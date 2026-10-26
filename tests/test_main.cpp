// Simple unit tests with no external library.
// Each CHECK prints a message if it fails. The program returns 1 if any check failed,
// which makes CTest report the test as failed.
#include <cmath>
#include <iostream>

#include "Vec2.h"

using eco::Vec2;

static int failures = 0;

#define CHECK(condition)                                                    \
    do {                                                                    \
        if (!(condition)) {                                                 \
            std::cerr << __FILE__ << ":" << __LINE__ << ": CHECK failed: "  \
                      << #condition << "\n";                                \
            ++failures;                                                     \
        }                                                                   \
    } while (false)

static void testDefaultIsZero() {
    Vec2 v;
    CHECK(v.getX() == 0.0);
    CHECK(v.getY() == 0.0);
}

static void testAddition() {
    Vec2 sum = Vec2(1.0, 2.0) + Vec2(3.0, 4.0);
    CHECK(sum == Vec2(4.0, 6.0));
}

static void testScale() {
    CHECK(Vec2(1.0, -2.0) * 3.0 == Vec2(3.0, -6.0));
}

static void testLength() {
    CHECK(std::abs(Vec2(3.0, 4.0).length() - 5.0) < 1e-9);
}

int main() {
    testDefaultIsZero();
    testAddition();
    testScale();
    testLength();

    if (failures == 0) {
        std::cout << "All tests passed.\n";
        return 0;
    }
    std::cerr << failures << " check(s) failed.\n";
    return 1;
}
