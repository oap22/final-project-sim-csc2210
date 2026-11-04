#include "sim/BatchRunner.h"

#include "sim/Simulation.h"

namespace eco {

BatchRunner::BatchRunner(const Config& config) : baseConfig(config) {
    // TODO
}

std::vector<BatchResult> BatchRunner::run(const std::vector<double>& /*ratios*/, int /*steps*/) {
    // TODO
    return {};
}

} // namespace eco
