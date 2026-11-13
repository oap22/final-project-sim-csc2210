#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <optional>

#include "raylib.h"

#include "core/Config.h"
#include "gui/PlaceTool.h"
#include "core/Position.h"
#include "world/World.h"

namespace eco {

// Draws the grid and lets the user place things on it.
class GridView {
public:
    void setArea(Rectangle newArea);
    void draw(const World& world);
    std::optional<Position> tileUnderMouse();
    void place(World& world, PlaceTool tool, Position pos, const Config& config);

private:
    Rectangle area{};
    int tileSize = 0;
    int columns = 0;
    int rows = 0;
};

} // namespace eco

#endif // GRIDVIEW_H
