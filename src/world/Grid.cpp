#include "world/Grid.h"

#include <stdexcept>

namespace eco {

Grid::Grid(int width, int height) : width(width), height(height) {
    // TODO: throw std::invalid_argument if width or height is 0 or less.
    // TODO: make width * height tiles.
}

Tile& Grid::at(Position /*pos*/) {
    // TODO: return the tile at pos.
    throw std::logic_error("TODO: Grid::at is not written yet");
}

bool Grid::inBounds(Position /*pos*/) const {
    // TODO
    return false;
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
