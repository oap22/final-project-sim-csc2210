#ifndef BATCHRESULTSVIEW_H
#define BATCHRESULTSVIEW_H

#include <vector>

#include "BatchResult.h"

namespace eco {

// Shows the results of batch mode (final ratio for each starting ratio).
class BatchResultsView {
public:
    void draw(const std::vector<BatchResult>& results);
};

} // namespace eco

#endif // BATCHRESULTSVIEW_H
