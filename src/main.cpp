// Entry point for the GUI program.
// Keep this file small: create the main objects and run the loop.
// All simulation logic belongs in the "core" library (src/ and include/),
// so it can be tested without a window.
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION // Put this in exactly one .cpp file.
#include "raygui.h"

#include "Vec2.h"

int main() {
    InitWindow(800, 600, "Term Project");
    SetTargetFPS(60);

    eco::Vec2 position(400.0, 300.0);
    eco::Vec2 velocity(2.0, 1.0);
    bool running = true;

    while (!WindowShouldClose()) {
        if (running) {
            position = position + velocity;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(static_cast<int>(position.getX()), static_cast<int>(position.getY()), 10.0f, DARKGREEN);
        if (GuiButton(Rectangle{10, 10, 100, 30}, running ? "Pause" : "Start")) {
            running = !running;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
