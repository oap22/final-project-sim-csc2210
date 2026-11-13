// Unit tests for the core library, using doctest.
// DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN makes doctest write main() for us.
// Put it in exactly one test file. Other test files only include <doctest/doctest.h>.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <algorithm>
#include <memory>
#include <vector>

#include "core/Config.h"
#include "core/Position.h"
#include "core/Random.h"
#include "core/Vec2.h"
#include "entities/Fox.h"
#include "entities/Rabbit.h"
#include "sim/Simulation.h"
#include "world/FillSettings.h"
#include "world/Grid.h"
#include "world/Weather.h"
#include "world/World.h"

using eco::Animal;
using eco::Config;
using eco::FillSettings;
using eco::Fox;
using eco::Grid;
using eco::Position;
using eco::Rabbit;
using eco::Random;
using eco::Simulation;
using eco::Species;
using eco::TileType;
using eco::Vec2;
using eco::Weather;
using eco::WeatherType;
using eco::World;

namespace {

Config smallConfig() {
    Config config{};
    config.gridWidth = 10;
    config.gridHeight = 10;
    config.seed = 42;
    config.rabbitBirthEnergy = 20;
    config.foxBirthEnergy = 30;
    return config;
}

int countGround(World& world, TileType type) {
    int count = 0;
    for (int y = 0; y < world.getGrid().getHeight(); ++y) {
        for (int x = 0; x < world.getGrid().getWidth(); ++x) {
            if (world.getGrid().at({x, y}).type == type) {
                ++count;
            }
        }
    }
    return count;
}

int countAnimals(World& world, Species species) {
    int count = 0;
    for (int y = 0; y < world.getGrid().getHeight(); ++y) {
        for (int x = 0; x < world.getGrid().getWidth(); ++x) {
            const Animal* animal = world.animalAt({x, y});
            if (animal != nullptr && animal->species() == species) {
                ++count;
            }
        }
    }
    return count;
}

std::vector<Position> tenPositions() {
    std::vector<Position> list;
    for (int x = 0; x < 10; ++x) {
        list.push_back(Position{x, 0});
    }
    return list;
}

} // namespace

TEST_CASE("default Vec2 is zero") {
    Vec2 v;
    CHECK(v.getX() == 0.0);
    CHECK(v.getY() == 0.0);
}

TEST_CASE("Vec2 addition") {
    Vec2 sum = Vec2(1.0, 2.0) + Vec2(3.0, 4.0);
    CHECK(sum == Vec2(4.0, 6.0));
}

TEST_CASE("Vec2 scale") {
    CHECK(Vec2(1.0, -2.0) * 3.0 == Vec2(3.0, -6.0));
}

TEST_CASE("Vec2 length") {
    // doctest::Approx compares doubles with a small tolerance.
    CHECK(Vec2(3.0, 4.0).length() == doctest::Approx(5.0));
}

TEST_CASE("Position equality") {
    CHECK(Position{1, 2} == Position{1, 2});
    CHECK_FALSE(Position{1, 2} == Position{9, 2});
    CHECK_FALSE(Position{1, 2} == Position{1, 9});
}

TEST_CASE("Grid size") {
    Grid grid(3, 2);
    CHECK(grid.getWidth() == 3);
    CHECK(grid.getHeight() == 2);
}

TEST_CASE("new Grid tiles are dirt") {
    Grid grid(3, 2);
    CHECK(grid.at({0, 0}).type == TileType::Dirt);
    CHECK(grid.at({2, 1}).type == TileType::Dirt);
}

TEST_CASE("Grid changes only the chosen tile") {
    Grid grid(3, 2);
    grid.at({2, 0}).type = TileType::Grass;
    CHECK(grid.at({2, 0}).type == TileType::Grass);
    CHECK(grid.at({0, 1}).type == TileType::Dirt);

    const Grid& readOnly = grid;
    CHECK(readOnly.at({2, 0}).type == TileType::Grass);
}

TEST_CASE("Grid inBounds") {
    Grid grid(3, 2);
    CHECK(grid.inBounds({0, 0}));
    CHECK(grid.inBounds({2, 1}));
    CHECK_FALSE(grid.inBounds({-1, 0}));
    CHECK_FALSE(grid.inBounds({0, -1}));
    CHECK_FALSE(grid.inBounds({3, 0}));
    CHECK_FALSE(grid.inBounds({0, 2}));
}

TEST_CASE("empty World tile is free") {
    World world(3, 2);
    CHECK(world.animalAt({1, 1}) == nullptr);
    CHECK(world.isFree({1, 1}));
}

TEST_CASE("added animals are found on their tile") {
    World world(3, 2);
    CHECK(world.addAnimal(std::make_unique<Rabbit>(Position{1, 1}, 20)));
    CHECK(world.addAnimal(std::make_unique<Fox>(Position{2, 1}, 30)));

    REQUIRE(world.animalAt({1, 1}) != nullptr);
    REQUIRE(world.animalAt({2, 1}) != nullptr);
    CHECK(world.animalAt({1, 1})->species() == Species::Rabbit);
    CHECK(world.animalAt({2, 1})->species() == Species::Fox);
    CHECK_FALSE(world.isFree({1, 1}));
}

TEST_CASE("addAnimal refuses a full tile") {
    World world(3, 2);
    CHECK(world.addAnimal(std::make_unique<Rabbit>(Position{1, 1}, 20)));
    CHECK_FALSE(world.addAnimal(std::make_unique<Fox>(Position{1, 1}, 30)));

    REQUIRE(world.animalAt({1, 1}) != nullptr);
    CHECK(world.animalAt({1, 1})->species() == Species::Rabbit);
}

TEST_CASE("addAnimal refuses an out-of-bounds tile") {
    World world(3, 2);
    CHECK_FALSE(world.addAnimal(std::make_unique<Rabbit>(Position{3, 0}, 20)));
    CHECK_FALSE(world.isFree({3, 0}));
}

TEST_CASE("removeAnimalAt removes only that animal") {
    World world(3, 2);
    world.addAnimal(std::make_unique<Rabbit>(Position{0, 0}, 20));
    world.addAnimal(std::make_unique<Fox>(Position{1, 0}, 30));

    world.removeAnimalAt({0, 0});

    CHECK(world.animalAt({0, 0}) == nullptr);
    CHECK(world.isFree({0, 0}));
    CHECK(world.animalAt({1, 0}) != nullptr);
}

TEST_CASE("removeAnimalAt on an empty tile changes nothing") {
    World world(3, 2);
    world.addAnimal(std::make_unique<Rabbit>(Position{0, 0}, 20));

    world.removeAnimalAt({2, 1});

    CHECK(world.animalAt({0, 0}) != nullptr);
}

TEST_CASE("shuffle keeps every position exactly once") {
    Random random(42);
    std::vector<Position> list = tenPositions();
    random.shuffle(list);

    REQUIRE(list.size() == 10);
    for (const Position& pos : tenPositions()) {
        CHECK(std::count(list.begin(), list.end(), pos) == 1);
    }
}

TEST_CASE("shuffle with the same seed gives the same order") {
    Random first(42);
    Random second(42);
    std::vector<Position> a = tenPositions();
    std::vector<Position> b = tenPositions();
    first.shuffle(a);
    second.shuffle(b);
    CHECK(a == b);
}

TEST_CASE("weather starts Normal") {
    Weather weather;
    CHECK(weather.getType() == WeatherType::Normal);
}

TEST_CASE("weather lasts the chosen steps, then goes back to Normal") {
    Weather weather;
    Random random(42);
    weather.setWeather(WeatherType::Drought, 2);

    CHECK(weather.getType() == WeatherType::Drought);
    weather.update(random);
    CHECK(weather.getType() == WeatherType::Drought);
    weather.update(random);
    CHECK(weather.getType() == WeatherType::Normal);
}

TEST_CASE("setting new weather replaces the old countdown") {
    Weather weather;
    Random random(42);
    weather.setWeather(WeatherType::Rain, 1);
    weather.setWeather(WeatherType::Drought, 2);

    weather.update(random);
    CHECK(weather.getType() == WeatherType::Drought);
}

TEST_CASE("fill at 50/50 gives exact counts") {
    World world(10, 10);
    Random random(42);
    world.fill(FillSettings{0.5, 0.5, 0.5, 0.5}, random, smallConfig());

    CHECK(countGround(world, TileType::Grass) == 25);
    CHECK(countGround(world, TileType::Plant) == 25);
    CHECK(countGround(world, TileType::Dirt) == 50);
    CHECK(countAnimals(world, Species::Rabbit) == 25);
    CHECK(countAnimals(world, Species::Fox) == 25);
}

TEST_CASE("fill follows each slider") {
    World world(10, 10);
    Random random(42);
    world.fill(FillSettings{1.0, 0.2, 0.1, 1.0}, random, smallConfig());

    CHECK(countGround(world, TileType::Grass) == 20);
    CHECK(countGround(world, TileType::Plant) == 80);
    CHECK(countGround(world, TileType::Dirt) == 0);
    CHECK(countAnimals(world, Species::Rabbit) == 10);
    CHECK(countAnimals(world, Species::Fox) == 0);
}

TEST_CASE("fill at 0% leaves dirt and no animals") {
    World world(10, 10);
    Random random(42);
    world.fill(FillSettings{0.0, 0.5, 0.0, 0.5}, random, smallConfig());

    CHECK(countGround(world, TileType::Dirt) == 100);
    CHECK(countAnimals(world, Species::Rabbit) == 0);
    CHECK(countAnimals(world, Species::Fox) == 0);
}

TEST_CASE("fill at 100% animals puts one on every tile") {
    World world(10, 10);
    Random random(42);
    world.fill(FillSettings{0.0, 0.5, 1.0, 0.0}, random, smallConfig());

    CHECK(countAnimals(world, Species::Fox) == 100);
}

TEST_CASE("fill replaces what was on the grid") {
    World world(10, 10);
    Random random(42);
    for (int x = 0; x < 10; ++x) {
        world.getGrid().at({x, 0}).type = TileType::Grass;
        world.addAnimal(std::make_unique<Fox>(Position{x, 0}, 30));
    }

    world.fill(FillSettings{0.0, 0.5, 0.0, 0.5}, random, smallConfig());

    CHECK(countGround(world, TileType::Grass) == 0);
    CHECK(countAnimals(world, Species::Fox) == 0);
}

TEST_CASE("a new Simulation is not filled") {
    Simulation simulation(smallConfig());
    CHECK(countGround(simulation.getWorld(), TileType::Dirt) == 100);
    CHECK(countAnimals(simulation.getWorld(), Species::Rabbit) == 0);
    CHECK(countAnimals(simulation.getWorld(), Species::Fox) == 0);
}

TEST_CASE("Simulation fillWorld fills its world") {
    Simulation simulation(smallConfig());
    simulation.fillWorld(FillSettings{0.5, 0.5, 0.5, 0.5});

    CHECK(countGround(simulation.getWorld(), TileType::Dirt) == 50);
    CHECK(countAnimals(simulation.getWorld(), Species::Rabbit) == 25);
}

TEST_CASE("Simulation steps count down the weather") {
    Simulation simulation(smallConfig());
    simulation.setWeather(WeatherType::Rain, 2);

    simulation.step();
    CHECK(simulation.getWeather().getType() == WeatherType::Rain);
    simulation.step();
    CHECK(simulation.getWeather().getType() == WeatherType::Normal);
}
