#include "world/Weather.h"

namespace eco {

// Counts down the weather chosen with setWeather, then goes back to Normal.
void Weather::update(Random& /*random*/) {
    // TODO: start random weather changes.
    if (stepsLeft > 0) {
        --stepsLeft;
        if (stepsLeft == 0) {
            type = WeatherType::Normal;
        }
    }
}

void Weather::setWeather(WeatherType newType, int steps) {
    type = newType;
    stepsLeft = steps;
}

WeatherType Weather::getType() const {
    // TODO
    return type;
}

double Weather::growthMultiplier() const {
    // TODO
    return 1.0;
}

} // namespace eco
