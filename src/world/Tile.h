#ifndef TILE_H
#define TILE_H

#include "world/TileType.h"

namespace eco {

// One square of the grid. It only holds data.
struct Tile {
    TileType type = TileType::Dirt;
    double nutrients = 0.0;
};

} // namespace eco

#endif // TILE_H
