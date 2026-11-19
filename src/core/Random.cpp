#include "core/Random.h"

#include <algorithm>

namespace eco {

Random::Random(unsigned seed) : engine(seed) {
    // TODO
}

int Random::nextInt(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(engine);
}

bool Random::chance(double probability) {
    std::bernoulli_distribution dist(probability);
    return dist(engine);
}

void Random::shuffle(std::vector<Position>& list) {
    std::shuffle(list.begin(), list.end(), engine);
}

} // namespace eco
