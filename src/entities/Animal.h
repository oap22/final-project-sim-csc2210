#ifndef ANIMAL_H
#define ANIMAL_H

#include "core/Config.h"
#include "core/Position.h"
#include "core/Random.h"
#include "entities/Species.h"

namespace eco {

class World; // World.h includes Animal.h, so we only declare World here.

// Base class for every animal. World keeps a list of Animal pointers
// and calls act() on each one.
class Animal {
public:
    Animal(Position pos, int energy);
    virtual ~Animal() = default;

    virtual void act(World& world, Random& random, const Config& config) = 0;
    virtual Species species() const = 0;

    bool isAlive() const;
    void die();
    Position getPosition() const;

protected:
    void moveTo(World& world, Position pos);
    void getOlder(int maxAge);

    Position position;
    int energy;
    int age;
    bool alive;
};

} // namespace eco

#endif // ANIMAL_H
