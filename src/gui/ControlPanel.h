#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "raylib.h"

#include "gui/ControlAction.h"
#include "gui/PlaceTool.h"

namespace eco {

// Buttons for start, stop, step, reset, the place tool, and the step limit.
class ControlPanel {
public:
    ControlAction draw(bool running);
    PlaceTool getSelectedTool() const;
    int getStepLimit() const;

private:
    Rectangle area{};
    PlaceTool selectedTool = PlaceTool::Grass;
    int stepLimit = 1;
};

} // namespace eco

#endif // CONTROLPANEL_H
