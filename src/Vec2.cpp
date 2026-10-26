#include "Vec2.h"

#include <cmath>

namespace eco {

Vec2::Vec2() : x(0.0), y(0.0) {}

Vec2::Vec2(double x, double y) : x(x), y(y) {}

double Vec2::getX() const { return x; }

double Vec2::getY() const { return y; }

double Vec2::length() const {
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator*(double scale) const {
    return Vec2(x * scale, y * scale);
}

bool Vec2::operator==(const Vec2& other) const {
    return x == other.x && y == other.y;
}

} // namespace eco
