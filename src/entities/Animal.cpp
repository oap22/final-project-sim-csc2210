#include "entities/Animal.h"

#include "world/World.h"

namespace eco {

Animal::Animal(Position pos, int energy)
    : position(pos), energy(energy), age(0), alive(true) {
}

bool Animal::isAlive() const {
    return alive;
}

void Animal::die() {
    alive = false;
}

Position Animal::getPosition() const {
    return position;
}

void Animal::moveTo(World& wrld, Position pos) {
    if (alive && wrld.isFree(pos)) {
        position = pos;
    }
}

void Animal::getOlder(int max) {
    if (!alive) {
        return;
    }
    ++age;
    if (age>=max) {
        die();
    }

}

} // namespace eco
