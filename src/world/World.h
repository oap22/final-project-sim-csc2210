#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "entities/Animal.h"
#include "core/Config.h"
#include "world/FillSettings.h"
#include "world/Grid.h"
#include "world/PopulationCounts.h"
#include "core/Position.h"
#include "core/Random.h"

namespace eco {

// The grid plus all animals. World owns every animal (unique_ptr).
class World {
public:
    World(int width, int height);

    Grid& getGrid();
    const Grid& getGrid() const;
    bool addAnimal(std::unique_ptr<Animal> animal);
    void removeAnimalAt(Position pos);
    void fill(const FillSettings& settings, Random& random, const Config& config);
    void addBirth(std::unique_ptr<Animal> baby);
    Animal* animalAt(Position pos) const; // Not the owner. Do not delete.
    bool isFree(Position pos) const;
    void step(Random& random, const Config& config, double growth);
    PopulationCounts count() const;

private:
    void growPlants(Random& random, const Config& config, double growth);
    void removeDead(const Config& config);
    void addBirthsToWorld();

    Grid grid;
    std::vector<std::unique_ptr<Animal>> animals;
    std::vector<std::unique_ptr<Animal>> births;
};

} // namespace eco

#endif // WORLD_H
