#ifndef FILLSETTINGS_H
#define FILLSETTINGS_H

namespace eco {

// How to fill the grid. Every value is a fraction from 0.0 to 1.0.
struct FillSettings {
    double groundCoverage; // Part of the tiles that get grass or flowers. The rest is dirt.
    double grassShare;     // Part of the covered tiles that are grass. The rest are flowers.
    double animalCoverage; // Part of the tiles that get an animal.
    double rabbitShare;    // Part of the animals that are rabbits. The rest are foxes.
};

} // namespace eco

#endif // FILLSETTINGS_H
