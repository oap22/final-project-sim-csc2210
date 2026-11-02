#ifndef WEATHER_H
#define WEATHER_H

#include "Random.h"
#include "WeatherType.h"

namespace eco {

// Rain and drought change how fast grass and plants grow.
class Weather {
public:
    void update(Random& random);
    void setWeather(WeatherType type, int steps);
    WeatherType getType() const;
    double growthMultiplier() const;

private:
    WeatherType type = WeatherType::Normal;
    int stepsLeft = 0;
};

} // namespace eco

#endif // WEATHER_H
