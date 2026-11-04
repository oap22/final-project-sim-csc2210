#ifndef HISTORY_H
#define HISTORY_H

#include <vector>

#include "world/PopulationCounts.h"

namespace eco {

// The population counts for every step. The graph and the
// "has it settled?" check read from here.
class History {
public:
    void record(const PopulationCounts& counts);
    const std::vector<PopulationCounts>& getRecords() const;
    bool anyExtinct() const;
    double averageRatio(int firstStep, int lastStep) const;
    bool hasSettled(int window, double tolerance) const;

private:
    std::vector<PopulationCounts> records;
};

} // namespace eco

#endif // HISTORY_H
