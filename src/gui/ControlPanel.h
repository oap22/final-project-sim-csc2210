#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "raylib.h"

#include "gui/ControlAction.h"
#include "gui/PlaceTool.h"

namespace eco {

// Buttons for start, stop, step, reset, the place tool, the speed slider,
// and the step limit.
class ControlPanel {
public:
    void setArea(Rectangle newArea);

    // Draws the panel and returns the button pressed this frame (or None).
    ControlAction draw(bool running);

    PlaceTool getSelectedTool() const;
    int getStepLimit() const;
    float getSpeed() const; // Simulation steps per second.

private:
    Rectangle area{};
    int toolIndex = 0;         // Matches the order of PlaceTool.
    float speed = 10.0f;       // Steps per second.
    int stepLimit = 1000;
    bool stepLimitEditing = false;
};

} // namespace eco

#endif // CONTROLPANEL_H
