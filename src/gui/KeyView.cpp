#include "gui/KeyView.h"

#include "raygui.h" // Declarations only. The code is built in main.cpp.

#include "gui/Palette.h"

namespace eco {

namespace {

constexpr int kEntryCount = 5;
constexpr int kSwatchSize = 16;

struct Entry {
    const char* name;
    int count;
    Color tile;
    bool hasAnimal;
    Color animal;
};

} // namespace

void KeyView::setArea(Rectangle newArea) {
    area = newArea;
}

void KeyView::draw(const PopulationCounts& counts, int step, int totalTiles) {
    GuiGroupBox(area, TextFormat("Step %d", step));

    const Color dirt = groundColor(TileType::Dirt);
    const Entry entries[kEntryCount] = {
        {"Grass", counts.grass, groundColor(TileType::Grass), false, BLANK},
        {"Flowers", counts.plants, groundColor(TileType::Plant), false, BLANK},
        {"Dirt", totalTiles - counts.grass - counts.plants, dirt, false, BLANK},
        {"Rabbits", counts.rabbits, dirt, true, animalColor(Species::Rabbit)},
        {"Foxes", counts.foxes, dirt, true, animalColor(Species::Fox)},
    };

    const float columnWidth = (area.width - 20) / kEntryCount;
    const float rowY = area.y + 20;

    for (int i = 0; i < kEntryCount; ++i) {
        const Entry& entry = entries[i];
        const float x = area.x + 10 + i * columnWidth;

        // Animals are drawn on a dirt tile, the same as on the grid.
        DrawRectangle(static_cast<int>(x), static_cast<int>(rowY), kSwatchSize, kSwatchSize, entry.tile);
        if (entry.hasAnimal) {
            DrawCircle(static_cast<int>(x) + kSwatchSize / 2, static_cast<int>(rowY) + kSwatchSize / 2,
                       kSwatchSize * 0.35f, entry.animal);
        }

        GuiLabel(Rectangle{x + kSwatchSize + 4, rowY - 2, columnWidth - kSwatchSize - 4, 20},
                 TextFormat("%d", entry.count));
        GuiLabel(Rectangle{x, rowY + 19, columnWidth, 20}, entry.name);
    }
}

} // namespace eco
