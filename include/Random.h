#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <vector>

#include "Position.h"

namespace eco {

// All random choices go through one Random object with a seed,
// so a run with the same seed is the same every time.
class Random {
public:
    explicit Random(unsigned seed);

    int nextInt(int low, int high);
    bool chance(double probability);
    void shuffle(std::vector<Position>& list);

private:
    std::mt19937 engine;
};

} // namespace eco

#endif // RANDOM_H
