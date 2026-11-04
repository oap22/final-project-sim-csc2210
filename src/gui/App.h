#ifndef APP_H
#define APP_H

#include "raylib.h"

#include "core/Config.h"
#include "gui/ControlAction.h"
#include "gui/ControlPanel.h"
#include "gui/GridView.h"
#include "gui/PopulationGraph.h"
#include "sim/Simulation.h"

namespace eco {

// The GUI program: owns the simulation and the views, and runs the window loop.
//
// Each frame does three things, in this order:
//   handleInput() - read the mouse (place things on the grid)
//   update()      - step the simulation when enough time has passed
//   draw()        - draw every view, then act on the button the user pressed
class App {
public:
    explicit App(const Config& config);

    void run();

private:
    void handleInput();
    void update();
    void draw();
    void applyAction(ControlAction action);
    void resetSimulation();
    void loadFont();
    void drawLabel(const char* text, int x, int y);

    Config config;
    Simulation simulation;
    GridView gridView;
    PopulationGraph graph;
    ControlPanel controls;
    bool running;
    Font font{};
    bool fontLoaded = false;
    float stepTimer; // Steps owed to the simulation. 1.0 means "do one step".
};

} // namespace eco

#endif // APP_H
