#ifndef BATCHRESULT_H
#define BATCHRESULT_H

#include "sim/History.h"

namespace eco {

// The result of one run in batch mode.
struct BatchResult {
    double startRatio = 0.0;
    bool survived = false;
    bool settled = false;
    double finalRatio = 0.0;
    History history;
};

} // namespace eco

#endif // BATCHRESULT_H
