#include "sim/History.h"

namespace eco {

void History::record(const PopulationCounts& /*counts*/) {
    // TODO
}

const std::vector<PopulationCounts>& History::getRecords() const {
    // TODO
    return records;
}

bool History::anyExtinct() const {
    // TODO
    return false;
}

double History::averageRatio(int /*firstStep*/, int /*lastStep*/) const {
    // TODO
    return 0.0;
}

bool History::hasSettled(int /*window*/, double /*tolerance*/) const {
    // TODO
    return false;
}

} // namespace eco
