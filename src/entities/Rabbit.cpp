#include "entities/Rabbit.h"

#include "world/World.h"
using namespace std;
namespace eco {
    Rabbit::Rabbit(Position pos, int energy) : Animal(pos, energy) {
    }

    void Rabbit::act(World& wrld, Random& rand, const Config& config) {
        if (!isAlive()) {return;}
        // Increment age and check if alive again
        getOlder(config.rabbitMaxAge);
        if (!isAlive()) {return;}
        //lose 1 energy per step
        --energy;
        if (energy<=0) {
            die();
            return;
        }
        Tile& currTile = wrld.getGrid().at(position);
        // If there is no food here, look for another tile.
        if (currTile.type == TileType::Dirt) {
            vector<Position> freeNeighbors;
            vector<Position> foodNeighbors;
            for (Position next :
                 wrld.getGrid().neighbors(position)) {
                if (!wrld.isFree(next)) {
                    continue;
                }
                freeNeighbors.push_back(next);
                TileType ground = wrld.getGrid().at(next).type;
                if (ground == TileType::Grass ||
                    ground == TileType::Plant) {
                    foodNeighbors.push_back(next);
                    }
                 }
            // Prefer food spaces else move randomly.
            const auto& options = foodNeighbors.empty()
            ? freeNeighbors : foodNeighbors;
            if (!options.empty()) {
                int index = rand.nextInt(0,static_cast<int>(options.size())-1);
                moveTo(wrld, options[index]);
            }
        }
        //Eat 1 time @ current pos
        eat(wrld.getGrid().at(position), config);
        const int babyEnergy = config.rabbitBirthEnergy;
        if (babyEnergy > 0 && energy >= 2 * babyEnergy) {
            vector<Position> freeNeighbors;
            for (Position next :wrld.getGrid().neighbors(position)) {
                if (wrld.isFree(next)) {
                    freeNeighbors.push_back(next);
                }
            }
            if (!freeNeighbors.empty()) {
                int index = rand.nextInt(0, static_cast<int>(freeNeighbors.size()) - 1);
                energy -= babyEnergy;
                wrld.addBirth(make_unique<Rabbit>(freeNeighbors[index], babyEnergy));
            }
        }
    }

    Species Rabbit::species() const {
        return Species::Rabbit;
    }

    void Rabbit::eat(Tile& tile, const Config& config) {
        if (tile.type==TileType::Grass) {
            energy+=config.grassFood;
            tile.type=TileType::Dirt;
        }
        else if (tile.type == TileType::Plant) {
            energy+=config.plantFood;
            tile.type=TileType::Dirt;
        }
    }
}
// namespace eco
