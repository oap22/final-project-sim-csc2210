#include "gui/App.h"

#include <string>

#include "raylib.h"
#include "raygui.h" // Declarations only. The code is built in main.cpp.

#include "world/WeatherType.h"

namespace eco {

namespace {

// Window and layout, in pixels. Grid on the left, panel and graph on the right.
constexpr int kWindowWidth = 1000;
constexpr int kWindowHeight = 640;
constexpr Rectangle kGridArea{10, 10, 640, 620};
constexpr Rectangle kPanelArea{660, 10, 330, 300};
constexpr Rectangle kGraphArea{660, 370, 330, 260};
constexpr int kStatusX = 660;
constexpr int kStatusY = 320;
constexpr float kFontSize = 20.0f;
constexpr const char* kFontFile = "assets/fonts/Lato-Regular.ttf";

const char* weatherName(WeatherType type) {
    switch (type) {
        case WeatherType::Rain:    return "Rain";
        case WeatherType::Drought: return "Drought";
        case WeatherType::Normal:  return "Normal";
    }
    return "Normal";
}

} // namespace

App::App(const Config& config)
    : config(config), simulation(config), running(false), stepTimer(0.0f) {
    gridView.setArea(kGridArea);
    controls.setArea(kPanelArea);
    graph.setArea(kGraphArea);
}

void App::run() {
    InitWindow(kWindowWidth, kWindowHeight, "Predator-Prey Simulation");
    SetTargetFPS(60);
    loadFont();

    while (!WindowShouldClose()) {
        handleInput();
        update();
        draw();
    }

    if (fontLoaded) {
        UnloadFont(font);
    }
    CloseWindow();
}

// Loads a TrueType font and gives it to both our text and raygui.
// The font file is copied next to the program by CMake. If it is missing,
// raylib's small default font is used instead.
void App::loadFont() {
    const std::string path = std::string(GetApplicationDirectory()) + kFontFile;
    if (FileExists(path.c_str())) {
        font = LoadFontEx(path.c_str(), 40, nullptr, 0); // 40 px glyphs, scaled down when drawn.
        SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
        GuiSetFont(font);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
        fontLoaded = true;
    } else {
        font = GetFontDefault();
    }
}

void App::drawLabel(const char* text, int x, int y) {
    DrawTextEx(font, text, Vector2{static_cast<float>(x), static_cast<float>(y)}, kFontSize, 1.0f, DARKGRAY);
}

// Holding the left mouse button paints the selected tool onto the grid.
void App::handleInput() {
    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        return;
    }
    auto tile = gridView.tileUnderMouse();
    if (tile) {
        gridView.place(simulation.getWorld(), controls.getSelectedTool(), *tile, config);
    }
}

// The screen draws 60 times a second. The simulation steps "speed" times a
// second. stepTimer collects the time between frames and pays out whole steps.
void App::update() {
    simulation.setStepLimit(controls.getStepLimit());

    if (!running) {
        return;
    }
    if (simulation.isFinished()) {
        running = false;
        return;
    }

    stepTimer += GetFrameTime() * controls.getSpeed();
    while (stepTimer >= 1.0f && !simulation.isFinished()) {
        simulation.step();
        stepTimer -= 1.0f;
    }
}

void App::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    gridView.draw(simulation.getWorld());
    graph.draw(simulation.getHistory());
    ControlAction action = controls.draw(running);

    const auto& records = simulation.getHistory().getRecords();
    if (!records.empty()) {
        const PopulationCounts& now = records.back();
        drawLabel(TextFormat("Step %d   Rabbits %d   Foxes %d", now.step, now.rabbits, now.foxes),
                  kStatusX, kStatusY);
    }
    drawLabel(TextFormat("Weather: %s", weatherName(simulation.getWeather().getType())),
              kStatusX, kStatusY + 28);

    EndDrawing();

    // Act on the button after the frame is drawn, so the state changes
    // do not happen in the middle of drawing.
    applyAction(action);
}

void App::applyAction(ControlAction action) {
    switch (action) {
        case ControlAction::Start:
            running = true;
            break;
        case ControlAction::Stop:
            running = false;
            break;
        case ControlAction::StepOnce:
            running = false;
            if (!simulation.isFinished()) {
                simulation.step();
            }
            break;
        case ControlAction::Reset:
            resetSimulation();
            break;
        case ControlAction::None:
            break;
    }
}

void App::resetSimulation() {
    simulation = Simulation(config);
    running = false;
    stepTimer = 0.0f;
}

} // namespace eco
