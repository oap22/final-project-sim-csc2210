#ifndef VEC2_H
#define VEC2_H

// A 2D vector for positions and velocities.
// This is an example class. Replace or extend it for your project.
// It is in the "eco" namespace, so it does not conflict with raylib's own
// Vector2 type.
namespace eco {

class Vec2 {
public:
    Vec2();
    Vec2(double x, double y);

    double getX() const;
    double getY() const;

    // Returns the length of the vector.
    double length() const;

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator*(double scale) const;
    bool operator==(const Vec2& other) const;

private:
    double x;
    double y;
};

} // namespace eco

#endif // VEC2_H
