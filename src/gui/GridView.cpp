#include "gui/GridView.h"

namespace eco {

void GridView::setArea(Rectangle newArea) {
    area = newArea;
}

void GridView::draw(const World& /*world*/) {
    // TODO
}

std::optional<Position> GridView::tileUnderMouse() {
    // TODO
    return std::nullopt;
}

void GridView::place(World& /*world*/, PlaceTool /*tool*/, Position /*pos*/, const Config& /*config*/) {
    // TODO
}

} // namespace eco
