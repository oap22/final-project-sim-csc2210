#include "world/Grid.h"

#include <stdexcept>

namespace eco {

Grid::Grid(int w, int h) {
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Width and height must be greater than 0");
    }
    width = w;
    height = h;
    tiles.resize(static_cast<std::size_t>(w) * static_cast<std::size_t>(h));
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

std::vector<Position> Grid::neighbors(Position pos) const {
    std::vector<Position> result;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            Position next{pos.x + dx, pos.y + dy};
            if (inBounds(next)) {
                result.push_back(next);
            }
        }
    }
    return result;
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}

} // namespace eco
