#include "gui/ControlPanel.h"

namespace eco {

ControlAction ControlPanel::draw(bool /*running*/) {
    // TODO
    return ControlAction::None;
}

PlaceTool ControlPanel::getSelectedTool() const {
    // TODO
    return selectedTool;
}

int ControlPanel::getStepLimit() const {
    // TODO
    return stepLimit;
}

} // namespace eco
