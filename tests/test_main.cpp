// Unit tests for the core library, using doctest.
// DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN makes doctest write main() for us.
// Put it in exactly one test file. Other test files only include <doctest/doctest.h>.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "Vec2.h"

using eco::Vec2;

TEST_CASE("default Vec2 is zero") {
    Vec2 v;
    CHECK(v.getX() == 0.0);
    CHECK(v.getY() == 0.0);
}

TEST_CASE("Vec2 addition") {
    Vec2 sum = Vec2(1.0, 2.0) + Vec2(3.0, 4.0);
    CHECK(sum == Vec2(4.0, 6.0));
}

TEST_CASE("Vec2 scale") {
    CHECK(Vec2(1.0, -2.0) * 3.0 == Vec2(3.0, -6.0));
}

TEST_CASE("Vec2 length") {
    // doctest::Approx compares doubles with a small tolerance.
    CHECK(Vec2(3.0, 4.0).length() == doctest::Approx(5.0));
}
