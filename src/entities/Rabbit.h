#ifndef RABBIT_H
#define RABBIT_H

#include "entities/Animal.h"
#include "world/Tile.h"

namespace eco {

// Eats grass and plants.
class Rabbit : public Animal {
public:
    Rabbit(Position pos, int energy);

    void act(World& world, Random& random, const Config& config) override;
    Species species() const override;

private:
    void eat(Tile& tile, const Config& config);
};

} // namespace eco

#endif // RABBIT_H
