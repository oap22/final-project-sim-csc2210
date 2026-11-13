#ifndef KEYVIEW_H
#define KEYVIEW_H

#include "raylib.h"

#include "world/PopulationCounts.h"

namespace eco {

// Shows what each grid color means and how many of each are on the grid now.
class KeyView {
public:
    void setArea(Rectangle newArea);
    void draw(const PopulationCounts& counts, int step, int totalTiles);

private:
    Rectangle area{};
};

} // namespace eco

#endif // KEYVIEW_H
