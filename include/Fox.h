#ifndef FOX_H
#define FOX_H

#include "Animal.h"

namespace eco {

// Hunts rabbits. Foxes live alone.
class Fox : public Animal {
public:
    Fox(Position pos, int energy);

    void act(World& world, Random& random, const Config& config) override;
    Species species() const override;

private:
    bool hunt(World& world, Random& random);
};

} // namespace eco

#endif // FOX_H
