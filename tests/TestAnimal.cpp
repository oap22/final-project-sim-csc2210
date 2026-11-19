
#include <doctest/doctest.h>

#include "entities/Animal.h"
#include "world/World.h"

using namespace eco;

class TestAnimal : public Animal {
public:
    using Animal::Animal;
    void act(World&, Random&, const Config&) override {
    }
    Species species() const override {
        return Species::Rabbit;
    }
    using Animal::moveTo;
    using Animal::getOlder;
};

TEST_CASE("Animal starts alive at its initial position") {
    TestAnimal animal({1, 2}, 20);
    CHECK(animal.isAlive());
    CHECK(animal.getPosition() == Position{1, 2});
}

TEST_CASE("Animal can be marked dead") {
    TestAnimal animal({1, 2}, 20);
    animal.die();
    CHECK_FALSE(animal.isAlive());
}

TEST_CASE("Animal moves to a free tile") {
    World world(5, 5);
    TestAnimal animal({1, 1}, 20);
    animal.moveTo(world, {2, 1});
    CHECK(animal.getPosition() == Position{2, 1});
}

TEST_CASE("Animal cannot move outside the world") {
    World world(5, 5);
    TestAnimal animal({1, 1}, 20);
    animal.moveTo(world, {-1, 1});
    CHECK(animal.getPosition() == Position{1, 1});
}

TEST_CASE("Animal dies upon reaching maximum age") {
    TestAnimal animal({1, 1}, 20);
    animal.getOlder(2);
    CHECK(animal.isAlive());
    animal.getOlder(2);
    CHECK_FALSE(animal.isAlive());
}
