#include "world/World.h"

#include <algorithm>
#include <cmath>
#include <utility>

#include "entities/Fox.h"
#include "entities/Rabbit.h"

namespace eco {

World::World(int width, int height) : grid(width, height) {
    // TODO
}

Grid& World::getGrid() {
    // TODO
    return grid;
}

const Grid& World::getGrid() const {
    return grid;
}

bool World::addAnimal(std::unique_ptr<Animal> animal) {
    if (!isFree(animal->getPosition())) {
        return false;
    }
    animals.push_back(std::move(animal));
    return true;
}

void World::removeAnimalAt(Position pos) {
    animals.erase(std::remove_if(animals.begin(), animals.end(),
                                 [pos](const std::unique_ptr<Animal>& animal) {
                                     return animal->getPosition() == pos;
                                 }),
                  animals.end());
}

void World::addBirth(std::unique_ptr<Animal> /*baby*/) {
    // TODO
}

// Replaces everything on the grid. Exact counts are placed on shuffled tiles,
// so the percentages hold every time. Ground and animals are shuffled apart.
void World::fill(const FillSettings& settings, Random& random, const Config& config) {
    animals.clear();

    std::vector<Position> positions;
    for (int y = 0; y < grid.getHeight(); ++y) {
        for (int x = 0; x < grid.getWidth(); ++x) {
            positions.push_back(Position{x, y});
        }
    }
    const int total = static_cast<int>(positions.size());

    random.shuffle(positions);
    const int covered = static_cast<int>(std::lround(total * settings.groundCoverage));
    const int grass = static_cast<int>(std::lround(covered * settings.grassShare));
    for (int i = 0; i < total; ++i) {
        TileType type = TileType::Dirt;
        if (i < grass) {
            type = TileType::Grass;
        } else if (i < covered) {
            type = TileType::Plant;
        }
        grid.at(positions[i]).type = type;
    }

    random.shuffle(positions);
    const int animalCount = static_cast<int>(std::lround(total * settings.animalCoverage));
    const int rabbits = static_cast<int>(std::lround(animalCount * settings.rabbitShare));
    for (int i = 0; i < animalCount; ++i) {
        if (i < rabbits) {
            addAnimal(std::make_unique<Rabbit>(positions[i], config.rabbitBirthEnergy));
        } else {
            addAnimal(std::make_unique<Fox>(positions[i], config.foxBirthEnergy));
        }
    }
}

Animal* World::animalAt(Position pos) const {
    for (const auto& animal : animals) {
        if (animal->getPosition() == pos) {
            return animal.get();
        }
    }
    return nullptr;
}

bool World::isFree(Position pos) const {
    return grid.inBounds(pos) && animalAt(pos) == nullptr;
}

void World::step(Random& /*random*/, const Config& /*config*/, double /*growth*/) {
    // TODO
}

// World does not know the step number, so counts.step stays 0 here.
PopulationCounts World::count() const {
    PopulationCounts counts;
    for (int y = 0; y < grid.getHeight(); ++y) {
        for (int x = 0; x < grid.getWidth(); ++x) {
            const TileType type = grid.at(Position{x, y}).type;
            if (type == TileType::Grass) {
                ++counts.grass;
            } else if (type == TileType::Plant) {
                ++counts.plants;
            }
        }
    }
    for (const auto& animal : animals) {
        if (animal->species() == Species::Rabbit) {
            ++counts.rabbits;
        } else {
            ++counts.foxes;
        }
    }
    return counts;
}

void World::growPlants(Random& /*random*/, const Config& /*config*/, double /*growth*/) {
    // TODO
}

void World::removeDead(const Config& /*config*/) {
    // TODO
}

void World::addBirthsToWorld() {
    // TODO
}

} // namespace eco
