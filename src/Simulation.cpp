#include "Simulation.h"

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
    // TODO
}

void Simulation::run(int /*steps*/) {
    // TODO
}

bool Simulation::isFinished() const {
    // TODO
    return false;
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

} // namespace eco
