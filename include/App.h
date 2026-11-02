#ifndef APP_H
#define APP_H

#include "Config.h"
#include "ControlPanel.h"
#include "GridView.h"
#include "PopulationGraph.h"
#include "Simulation.h"

namespace eco {

// The GUI program: owns the simulation and the views, and runs the window loop.
class App {
public:
    explicit App(const Config& config);

    void run();

private:
    void handleInput();
    void draw();

    Simulation simulation;
    GridView gridView;
    PopulationGraph graph;
    ControlPanel controls;
    bool running;
};

} // namespace eco

#endif // APP_H
