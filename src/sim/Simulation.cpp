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
    weather.update(random);
    // TODO: the rest of the step.
    ++stepCount;
}

void Simulation::run(int /*steps*/) {
    // TODO
}

bool Simulation::isFinished() const {
    // TODO
    return false;
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

void Simulation::setStepLimit(int /*limit*/) {
    // TODO
}

void Simulation::fillWorld(const FillSettings& settings) {
    world.fill(settings, random, config);
}

void Simulation::setWeather(WeatherType type, int steps) {
    weather.setWeather(type, steps);
}

} // namespace eco
