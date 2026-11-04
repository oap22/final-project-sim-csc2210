#include "world/Weather.h"

namespace eco {

void Weather::update(Random& /*random*/) {
    // TODO
}

void Weather::setWeather(WeatherType /*type*/, int /*steps*/) {
    // TODO
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
