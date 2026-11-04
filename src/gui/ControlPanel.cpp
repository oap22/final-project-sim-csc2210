#include "gui/ControlPanel.h"

#include "raygui.h" // Declarations only. The code is built in main.cpp.

namespace eco {

namespace {

constexpr float kRowHeight = 30.0f;
constexpr float kMinSpeed = 1.0f;
constexpr float kMaxSpeed = 60.0f;
constexpr int kMaxStepLimit = 100000;

} // namespace

void ControlPanel::setArea(Rectangle newArea) {
    area = newArea;
}

// raygui is "immediate mode": every call both draws the widget and reports
// what the user did to it this frame. GuiButton returns true on the click.
ControlAction ControlPanel::draw(bool running) {
    ControlAction action = ControlAction::None;

    GuiGroupBox(area, "Controls");

    const float x = area.x + 10;
    const float width = area.width - 20;
    const float half = (width - 10) / 2;
    float y = area.y + 20;

    // Start / Stop and Step
    if (GuiButton(Rectangle{x, y, half, kRowHeight}, running ? "Stop" : "Start")) {
        action = running ? ControlAction::Stop : ControlAction::Start;
    }
    if (GuiButton(Rectangle{x + half + 10, y, half, kRowHeight}, "Step")) {
        action = ControlAction::StepOnce;
    }
    y += kRowHeight + 10;

    // Reset
    if (GuiButton(Rectangle{x, y, width, kRowHeight}, "Reset")) {
        action = ControlAction::Reset;
    }
    y += kRowHeight + 20;

    // Place tool. The text order must match the PlaceTool enum.
    GuiLabel(Rectangle{x, y, width, 20}, "Place tool");
    y += 25;
    GuiToggleGroup(Rectangle{x, y, 56, kRowHeight}, "Grass;Plant;Rabbit;Fox;Erase", &toolIndex);
    y += kRowHeight + 20;

    // Speed slider
    GuiLabel(Rectangle{x, y, width, 20}, TextFormat("Speed: %d steps/s", static_cast<int>(speed)));
    y += 25;
    GuiSliderBar(Rectangle{x + 40, y, width - 80, 20}, "Slow", "Fast", &speed, kMinSpeed, kMaxSpeed);
    y += 40;

    // Step limit. The spinner returns true when the user clicks it,
    // which switches text editing on or off.
    // We draw the "Step limit" label ourselves so we control the gap.
    // raygui would put its own label flush against the spinner.
    GuiLabel(Rectangle{x, y, 90, kRowHeight}, "Step limit");
    if (GuiSpinner(Rectangle{x + 100, y, width - 100, kRowHeight}, nullptr, &stepLimit,
                   1, kMaxStepLimit, stepLimitEditing)) {
        stepLimitEditing = !stepLimitEditing;
    }

    return action;
}

PlaceTool ControlPanel::getSelectedTool() const {
    return static_cast<PlaceTool>(toolIndex);
}

int ControlPanel::getStepLimit() const {
    return stepLimit;
}

float ControlPanel::getSpeed() const {
    return speed;
}

} // namespace eco
