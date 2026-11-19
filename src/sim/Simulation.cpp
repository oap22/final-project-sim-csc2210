#include "sim/Simulation.h"

namespace eco {

Simulation::Simulation(const Config& config)
    : config(config),
      random(config.seed),
      world(config.gridWidth, config.gridHeight),
      stepCount(0),
      stepLimit(0) {
    // TODO
}

void Simulation::step() {
    if (isFinished()) {
        return;
    }
    weather.update(random);
    world.step(random, config, weather.growthMultiplier());
    ++stepCount;
    PopulationCounts counts = world.count();
    counts.step = stepCount;
    history.record(counts);
}

void Simulation::run(int /*steps*/) {
    // TODO
}

bool Simulation::isFinished() const {
    return stepLimit>0&&stepCount>=stepLimit;
}

int Simulation::getStepCount() const {
    return stepCount;
}

World& Simulation::getWorld() {
    // TODO
    return world;
}

const History& Simulation::getHistory() const {
    // TODO
    return history;
}

const Weather& Simulation::getWeather() const {
    // TODO
    return weather;
}

void Simulation::setStepLimit(int limit) {
    stepLimit = limit;
}

void Simulation::fillWorld(const FillSettings& settings) {
    world.fill(settings, random, config);
}

void Simulation::setWeather(WeatherType type, int steps) {
    weather.setWeather(type, steps);
}

} // namespace eco
