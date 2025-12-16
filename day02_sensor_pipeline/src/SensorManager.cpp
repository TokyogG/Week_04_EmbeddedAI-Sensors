#include "SensorManager.hpp"
#include <iostream>

bool SensorManager::addSensor(ISensor* s) {
    if (!s) return false;
    if (count_ >= sensors_.size()) return false;
    sensors_[count_++] = s;
    return true;
}

bool SensorManager::initAll() {
    for (std::size_t i = 0; i < count_; ++i) {
        if (!sensors_[i]->init()) {
            std::cerr << "[SensorManager] init failed: " << sensors_[i]->name() << "\n";
            return false;
        }
    }
    return true;
}

void SensorManager::tick() {
    // Real-time side: acquire + enqueue (keep it short)
    for (std::size_t i = 0; i < count_; ++i) {
        SensorSample sample{};
        if (sensors_[i]->read(sample)) {
            queues_[i].push(sample);
        }
    }
}

bool SensorManager::popSample(std::size_t sensor_index, SensorSample& out) {
    if (sensor_index >= count_) return false;
    return queues_[sensor_index].pop(out);
}