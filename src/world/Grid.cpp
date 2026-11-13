#include "world/Grid.h"

#include <stdexcept>

namespace eco {

Grid::Grid(int width, int height) : width(width), height(height), tiles(width * height) {
    // TODO: throw std::invalid_argument if width or height is 0 or less.
}

// Tiles are stored row after row in one vector.
Tile& Grid::at(Position pos) {
    return tiles.at(pos.y * width + pos.x);
}

const Tile& Grid::at(Position pos) const {
    return tiles.at(pos.y * width + pos.x);
}

bool Grid::inBounds(Position pos) const {
    return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
}

std::vector<Position> Grid::neighbors(Position /*pos*/) const {
    // TODO: return the tiles around pos that are in bounds.
    return {};
}

int Grid::getWidth() const {
    // TODO
    return width;
}

int Grid::getHeight() const {
    // TODO
    return height;
}

} // namespace eco
