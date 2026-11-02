#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <optional>

#include "raylib.h"

#include "PlaceTool.h"
#include "Position.h"
#include "World.h"

namespace eco {

// Draws the grid and lets the user place things on it.
class GridView {
public:
    void draw(const World& world);
    std::optional<Position> tileUnderMouse();
    void place(World& world, PlaceTool tool, Position pos);

private:
    Rectangle area{};
    int tileSize = 0;
};

} // namespace eco

#endif // GRIDVIEW_H
