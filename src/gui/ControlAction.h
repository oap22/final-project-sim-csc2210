#ifndef CONTROLACTION_H
#define CONTROLACTION_H

namespace eco {

// The button the user pressed in the control panel this frame.
enum class ControlAction {
    None,
    Start,
    Stop,
    StepOnce,
    Reset,
    FillGrid,
    SetWeather
};

} // namespace eco

#endif // CONTROLACTION_H
