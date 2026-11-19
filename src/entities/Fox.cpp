#include "entities/Fox.h"

#include "world/World.h"
using namespace std;
namespace eco {

Fox::Fox(Position pos, int energy) : Animal(pos, energy) {
}

void Fox::act(World& wrld, Random& rand, const Config& config) {
    if (!isAlive()) {return;}
    getOlder(config.foxMaxAge);
    if (!isAlive()) {return;}
    // Lose energy 1 time per step
    --energy;
    if (energy <= 0) {
        die();
        return;
    }
    // Hunt rabbits that are near
    if (hunt(wrld, rand)) {
        energy += config.rabbitFood;
    } else {
        // No rabbit nearby so move to a free tile (could put rabbit tracking here)
        vector<Position> freeNeighbors;
        for (Position next:wrld.getGrid().neighbors(position)) {
            if (wrld.isFree(next)) {
                freeNeighbors.push_back(next);
            }
        }
        if (!freeNeighbors.empty()) {
            int index = rand.nextInt(0, static_cast<int>(freeNeighbors.size()) - 1);
            moveTo(wrld, freeNeighbors[index]);
        }
    }
    const int babyEnergy = config.foxBirthEnergy;
    if (babyEnergy > 0 && energy >= 2 * babyEnergy) {
        vector<Position> freeNeighbors;
        for (Position next :
             wrld.getGrid().neighbors(position)) {
            if (wrld.isFree(next)) {
                freeNeighbors.push_back(next);
            }
        }
        if (!freeNeighbors.empty()) {
            int index = rand.nextInt(0, static_cast<int>(freeNeighbors.size()) - 1);
            energy -= babyEnergy;
            wrld.addBirth(make_unique<Fox>(
                freeNeighbors[index], babyEnergy));
        }
    }
}

Species Fox::species() const {
    return Species::Fox;
}

bool Fox::hunt(World& wrld, Random& rand) {
    vector<Animal*> rabbits;
    // Find all alive rabbits on tiles next to this tile
    for (Position next :
         wrld.getGrid().neighbors(position)) {
        Animal* animal = wrld.animalAt(next);
        if (animal != nullptr &&
            animal->isAlive() &&
            animal->species() == Species::Rabbit) {
            rabbits.push_back(animal);
            }
         }
    // No rabbits are here
    if (rabbits.empty()) {
        return false;
    }
    // Choose 1 sad lil rabbit and brutally eliminate it
    int index = rand.nextInt(0, static_cast<int>(rabbits.size()) - 1);
    rabbits[index]->die();
    return true;
}

} // namespace eco
