#include "Rabbit.h"

#include "World.h"

namespace eco {

Rabbit::Rabbit(Position pos, int energy) : Animal(pos, energy) {
    // TODO
}

void Rabbit::act(World& /*world*/, Random& /*random*/, const Config& /*config*/) {
    // TODO
}

Species Rabbit::species() const {
    // TODO
    return Species::Rabbit;
}

void Rabbit::eat(Tile& /*tile*/, const Config& /*config*/) {
    // TODO
}

} // namespace eco
