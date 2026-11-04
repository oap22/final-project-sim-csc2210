#include "world/World.h"

namespace eco {

World::World(int width, int height) : grid(width, height) {
    // TODO
}

Grid& World::getGrid() {
    // TODO
    return grid;
}

bool World::addAnimal(std::unique_ptr<Animal> /*animal*/) {
    // TODO: return false for a full or out-of-bounds tile.
    return false;
}

void World::addBirth(std::unique_ptr<Animal> /*baby*/) {
    // TODO
}

Animal* World::animalAt(Position /*pos*/) const {
    // TODO: return the animal on pos, or nullptr.
    return nullptr;
}

bool World::isFree(Position /*pos*/) const {
    // TODO
    return false;
}

void World::step(Random& /*random*/, const Config& /*config*/, double /*growth*/) {
    // TODO
}

PopulationCounts World::count() const {
    // TODO
    return {};
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
