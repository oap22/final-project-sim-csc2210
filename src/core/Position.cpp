#include "core/Position.h"

namespace eco {

bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

} // namespace eco
