#ifndef PALETTE_H
#define PALETTE_H

#include "raylib.h"

#include "entities/Species.h"
#include "world/TileType.h"

namespace eco {

// The colors of the grid, in one place so the key always matches it.
inline Color groundColor(TileType type) {
    switch (type) {
        case TileType::Grass: return Color{126, 170, 100, 255};
        case TileType::Plant: return VIOLET;
        case TileType::Dirt:  return BEIGE;
    }
    return BEIGE;
}

inline Color animalColor(Species species) {
    return species == Species::Rabbit ? WHITE : ORANGE;
}

} // namespace eco

#endif // PALETTE_H
