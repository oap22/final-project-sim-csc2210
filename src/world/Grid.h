#ifndef GRID_H
#define GRID_H

#include <vector>

#include "core/Position.h"
#include "world/Tile.h"

namespace eco {

// The 2D map of tiles.
class Grid {
public:
    Grid(int width, int height);

    Tile& at(Position pos);
    bool inBounds(Position pos) const;
    std::vector<Position> neighbors(Position pos) const;
    int getWidth() const;
    int getHeight() const;

private:
    int width;
    int height;
    std::vector<Tile> tiles;
};

} // namespace eco

#endif // GRID_H
