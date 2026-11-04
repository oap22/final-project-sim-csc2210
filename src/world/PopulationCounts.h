#ifndef POPULATIONCOUNTS_H
#define POPULATIONCOUNTS_H

namespace eco {

// How many of each thing exist after one step.
struct PopulationCounts {
    int step = 0;
    int grass = 0;
    int plants = 0;
    int rabbits = 0;
    int foxes = 0;
};

} // namespace eco

#endif // POPULATIONCOUNTS_H
