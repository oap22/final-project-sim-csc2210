#ifndef SIMULATION_H
#define SIMULATION_H

#include "core/Config.h"
#include "sim/History.h"
#include "core/Random.h"
#include "world/FillSettings.h"
#include "world/Weather.h"
#include "world/WeatherType.h"
#include "world/World.h"

namespace eco {

// Owns everything for one run and does one step at a time.
class Simulation {
public:
    explicit Simulation(const Config& config);

    void step();
    void run(int steps);
    bool isFinished() const;
    int getStepCount() const;
    World& getWorld();
    const History& getHistory() const;
    const Weather& getWeather() const;
    void setStepLimit(int limit);
    void fillWorld(const FillSettings& settings);
    void setWeather(WeatherType type, int steps);

private:
    Config config;
    Random random;
    World world;
    Weather weather;
    History history;
    int stepCount;
    int stepLimit;
};

} // namespace eco

#endif // SIMULATION_H
