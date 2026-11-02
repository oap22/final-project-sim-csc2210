#include "Animal.h"

#include "World.h"

namespace eco {

Animal::Animal(Position pos, int energy)
    : position(pos), energy(energy), age(0), alive(true) {
    // TODO
}

bool Animal::isAlive() const {
    // TODO
    return alive;
}

void Animal::die() {
    // TODO: mark the animal as dead. World removes it at the end of the step.
}

Position Animal::getPosition() const {
    // TODO
    return position;
}

void Animal::moveTo(World& /*world*/, Position /*pos*/) {
    // TODO
}

void Animal::getOlder(int /*maxAge*/) {
    // TODO
}

} // namespace eco
