#include "gui/SetupPanel.h"

#include "raygui.h" // Declarations only. The code is built in main.cpp.

namespace eco {

namespace {

constexpr float kRowHeight = 30.0f;
constexpr float kSliderRowHeight = 30.0f;
constexpr float kSliderSideWidth = 95.0f; // Room for the text on each side of a slider.
constexpr float kFillBoxHeight = 186.0f;
constexpr float kWeatherBoxHeight = 134.0f;
constexpr float kBoxGap = 10.0f;
constexpr int kMaxWeatherSteps = 100000;

const char* weatherName(WeatherType type) {
    switch (type) {
        case WeatherType::Rain:    return "Rain";
        case WeatherType::Drought: return "Drought";
        case WeatherType::Normal:  return "Normal";
    }
    return "Normal";
}

int rounded(float percent) {
    return static_cast<int>(percent + 0.5f);
}

// Draws one 0 to 100 slider with text on each side. Returns the y of the next row.
float drawPercentSlider(float x, float y, float width, const char* left, const char* right,
                        float* value) {
    GuiSliderBar(Rectangle{x + kSliderSideWidth, y, width - 2 * kSliderSideWidth, 20},
                 left, right, value, 0.0f, 100.0f);
    return y + kSliderRowHeight;
}

} // namespace

void SetupPanel::setArea(Rectangle newArea) {
    area = newArea;
}

ControlAction SetupPanel::draw(WeatherType currentWeather) {
    ControlAction action = ControlAction::None;

    const float x = area.x + 10;
    const float width = area.width - 20;

    // Fill grid
    GuiGroupBox(Rectangle{area.x, area.y, area.width, kFillBoxHeight}, "Fill grid");
    float y = area.y + 24;

    y = drawPercentSlider(x, y, width, "Ground", TextFormat("%d%%", rounded(groundCoverage)),
                          &groundCoverage);
    y = drawPercentSlider(x, y, width, TextFormat("Grass %d%%", 100 - rounded(flowerPercent)),
                          TextFormat("%d%% Flowers", rounded(flowerPercent)), &flowerPercent);
    y = drawPercentSlider(x, y, width, "Animals", TextFormat("%d%%", rounded(animalCoverage)),
                          &animalCoverage);
    y = drawPercentSlider(x, y, width, TextFormat("Rabbits %d%%", 100 - rounded(foxPercent)),
                          TextFormat("%d%% Foxes", rounded(foxPercent)), &foxPercent);

    const float half = (width - 10) / 2;
    if (GuiButton(Rectangle{x, y, half, kRowHeight}, "Fill grid")) {
        action = ControlAction::FillGrid;
    }
    // Only moves the sliders. The grid changes when "Fill grid" is pressed.
    if (GuiButton(Rectangle{x + half + 10, y, half, kRowHeight}, "Reset to 50/50")) {
        groundCoverage = 50.0f;
        flowerPercent = 50.0f;
        animalCoverage = 50.0f;
        foxPercent = 50.0f;
    }

    // Weather
    y = area.y + kFillBoxHeight + kBoxGap;
    GuiGroupBox(Rectangle{area.x, y, area.width, kWeatherBoxHeight}, "Weather");
    y += 24;

    GuiLabel(Rectangle{x, y, width, 20},
             TextFormat("Current weather: %s", weatherName(currentWeather)));
    y += 28;

    // The text order must match the WeatherType enum.
    GuiToggleGroup(Rectangle{x, y, (width - 4) / 3, kRowHeight}, "Normal;Rain;Drought", &weatherIndex);
    y += kRowHeight + 10;

    // Steps and the Set button share one row.
    GuiLabel(Rectangle{x, y, 45, kRowHeight}, "Steps");
    if (GuiSpinner(Rectangle{x + 50, y, 130, kRowHeight}, nullptr, &weatherSteps,
                   1, kMaxWeatherSteps, weatherStepsEditing)) {
        weatherStepsEditing = !weatherStepsEditing;
    }
    if (GuiButton(Rectangle{x + 190, y, width - 190, kRowHeight}, "Set weather")) {
        action = ControlAction::SetWeather;
    }

    return action;
}

FillSettings SetupPanel::getFillSettings() const {
    return FillSettings{groundCoverage / 100.0, 1.0 - flowerPercent / 100.0,
                        animalCoverage / 100.0, 1.0 - foxPercent / 100.0};
}

WeatherType SetupPanel::getWeatherType() const {
    return static_cast<WeatherType>(weatherIndex);
}

int SetupPanel::getWeatherSteps() const {
    return weatherSteps;
}

} // namespace eco
