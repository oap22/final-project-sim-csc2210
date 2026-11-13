#ifndef SETUPPANEL_H
#define SETUPPANEL_H

#include "raylib.h"

#include "gui/ControlAction.h"
#include "world/FillSettings.h"
#include "world/WeatherType.h"

namespace eco {

// The far-right column: fill the grid by percentage and choose the weather.
// Nothing here changes the simulation until the user presses a button.
class SetupPanel {
public:
    void setArea(Rectangle newArea);

    // Draws the panel and returns the button pressed this frame (or None).
    ControlAction draw(WeatherType currentWeather);

    FillSettings getFillSettings() const;
    WeatherType getWeatherType() const;
    int getWeatherSteps() const;

private:
    Rectangle area{};
    // Slider values, in percent. Each mix slider measures its right-hand side.
    float groundCoverage = 50.0f;
    float flowerPercent = 50.0f;
    float animalCoverage = 50.0f;
    float foxPercent = 50.0f;
    int weatherIndex = 0; // Matches the order of WeatherType.
    int weatherSteps = 50;
    bool weatherStepsEditing = false;
};

} // namespace eco

#endif // SETUPPANEL_H
