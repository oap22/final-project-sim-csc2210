#ifndef CONFIG_H
#define CONFIG_H

namespace eco {

// Every number we tune. Tests can make a small, simple config.
// TODO: choose default values for the fields below.
struct Config {
    int gridWidth;
    int gridHeight;
    unsigned seed;
    double grassSpreadChance;
    double plantSpreadChance;
    int grassFood;
    int plantFood;
    int rabbitFood;
    int rabbitMaxAge;
    int foxMaxAge;
    int rabbitBirthEnergy;
    int foxBirthEnergy;
    double deathNutrients;
    int settleWindow = 500;
    double settleTolerance = 0.02;
};

} // namespace eco

#endif // CONFIG_H
