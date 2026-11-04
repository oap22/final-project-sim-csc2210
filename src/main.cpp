// Entry point for the GUI program.
// Keep this file small: create the main objects and run the loop.
// All simulation logic belongs in the logic libraries (src/core, world,
// entities, sim), so it can be tested without a window.
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "core/Config.h"
#include "gui/App.h"

// Starting numbers for the simulation.
// TODO: tune these values. They are placeholders to get the window running.
static eco::Config makeDefaultConfig() {
    eco::Config config;
    config.gridWidth = 40;
    config.gridHeight = 30;
    config.seed = 42;
    config.grassSpreadChance = 0.05;
    config.plantSpreadChance = 0.02;
    config.grassFood = 5;
    config.plantFood = 10;
    config.rabbitFood = 8;
    config.rabbitMaxAge = 200;
    config.foxMaxAge = 300;
    config.rabbitBirthEnergy = 20;
    config.foxBirthEnergy = 30;
    config.deathNutrients = 1.0;
    return config;
}

int main() {
    eco::App app(makeDefaultConfig());
    app.run();
    return 0;
}
