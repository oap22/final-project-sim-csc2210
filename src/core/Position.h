#ifndef POSITION_H
#define POSITION_H

namespace eco {

// A tile location on the grid.
struct Position {
    int x = 0;
    int y = 0;

    bool operator==(const Position& other) const;
};

} // namespace eco

#endif // POSITION_H
