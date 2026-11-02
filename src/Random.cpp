#include "Random.h"

namespace eco {

Random::Random(unsigned seed) : engine(seed) {
    // TODO
}

int Random::nextInt(int low, int /*high*/) {
    // TODO: return a random number from low to high.
    return low;
}

bool Random::chance(double /*probability*/) {
    // TODO: return true with the given probability.
    return false;
}

void Random::shuffle(std::vector<Position>& /*list*/) {
    // TODO: put the list in a random order.
}

} // namespace eco
