#include "Fox.h"

#include "World.h"

namespace eco {

Fox::Fox(Position pos, int energy) : Animal(pos, energy) {
    // TODO
}

void Fox::act(World& /*world*/, Random& /*random*/, const Config& /*config*/) {
    // TODO
}

Species Fox::species() const {
    // TODO
    return Species::Fox;
}

bool Fox::hunt(World& /*world*/, Random& /*random*/) {
    // TODO
    return false;
}

} // namespace eco
