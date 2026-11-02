#ifndef BATCHRUNNER_H
#define BATCHRUNNER_H

#include <vector>

#include "BatchResult.h"
#include "Config.h"

namespace eco {

// Runs one Simulation for each starting ratio, with no window.
class BatchRunner {
public:
    explicit BatchRunner(const Config& config);

    std::vector<BatchResult> run(const std::vector<double>& ratios, int steps);

private:
    Config baseConfig;
};

} // namespace eco

#endif // BATCHRUNNER_H
