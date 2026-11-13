#include "gui/GridView.h"

#include <algorithm>
#include <memory>

#include "entities/Fox.h"
#include "entities/Rabbit.h"
#include "gui/Palette.h"

namespace eco {

void GridView::setArea(Rectangle newArea) {
    area = newArea;
}

// Draws every tile as a square in its ground color, with any animal as a
// circle on top. The tile under the mouse gets a black outline.
void GridView::draw(const World& world) {
    const Grid& grid = world.getGrid();
    columns = grid.getWidth();
    rows = grid.getHeight();

    // Use the largest whole-pixel square that fits both directions.
    tileSize = std::min(static_cast<int>(area.width) / columns,
                        static_cast<int>(area.height) / rows);

    const int left = static_cast<int>(area.x);
    const int top = static_cast<int>(area.y);

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            const Position pos{x, y};
            const int tileX = left + x * tileSize;
            const int tileY = top + y * tileSize;
            DrawRectangle(tileX, tileY, tileSize, tileSize, groundColor(grid.at(pos).type));
            DrawRectangleLines(tileX, tileY, tileSize, tileSize, LIGHTGRAY);

            if (const Animal* animal = world.animalAt(pos)) {
                DrawCircle(tileX + tileSize / 2, tileY + tileSize / 2, tileSize * 0.35f,
                           animalColor(animal->species()));
            }
        }
    }

    if (const std::optional<Position> hovered = tileUnderMouse()) {
        const Rectangle outline{static_cast<float>(left + hovered->x * tileSize),
                                static_cast<float>(top + hovered->y * tileSize),
                                static_cast<float>(tileSize), static_cast<float>(tileSize)};
        DrawRectangleLinesEx(outline, 2.0f, BLACK);
    }
}

// Returns the tile under the mouse, or nothing when the mouse is off the grid.
// Before the first draw the bounds are empty, so this also returns nothing.
std::optional<Position> GridView::tileUnderMouse() {
    const Rectangle bounds{area.x, area.y, static_cast<float>(columns * tileSize),
                           static_cast<float>(rows * tileSize)};
    const Vector2 mouse = GetMousePosition();
    if (!CheckCollisionPointRec(mouse, bounds)) {
        return std::nullopt;
    }
    return Position{static_cast<int>(mouse.x - area.x) / tileSize,
                    static_cast<int>(mouse.y - area.y) / tileSize};
}

// Grass and Plant change the ground and keep any animal on the tile.
// Rabbit and Fox replace any animal on the tile and keep the ground.
// Erase makes the tile plain dirt with no animal.
void GridView::place(World& world, PlaceTool tool, Position pos, const Config& config) {
    Tile& tile = world.getGrid().at(pos);
    switch (tool) {
        case PlaceTool::Grass:
            tile.type = TileType::Grass;
            break;
        case PlaceTool::Plant:
            tile.type = TileType::Plant;
            break;
        case PlaceTool::Rabbit:
            world.removeAnimalAt(pos);
            world.addAnimal(std::make_unique<Rabbit>(pos, config.rabbitBirthEnergy));
            break;
        case PlaceTool::Fox:
            world.removeAnimalAt(pos);
            world.addAnimal(std::make_unique<Fox>(pos, config.foxBirthEnergy));
            break;
        case PlaceTool::Erase:
            tile.type = TileType::Dirt;
            world.removeAnimalAt(pos);
            break;
    }
}

} // namespace eco
