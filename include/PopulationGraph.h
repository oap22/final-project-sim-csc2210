#ifndef POPULATIONGRAPH_H
#define POPULATIONGRAPH_H

#include "raylib.h"

#include "History.h"

namespace eco {

// Draws the live population graph.
class PopulationGraph {
public:
    void draw(const History& history);

private:
    Rectangle area{};
};

} // namespace eco

#endif // POPULATIONGRAPH_H
