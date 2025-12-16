#pragma once
#include <array>
#include <cstddef>
#include <chrono>
#include <cstdint>

#include "ISensor.hpp"
#include "SensorTypes.hpp"
#include "RingBuffer.hpp"

class SensorManager {
public:
    using SteadyClock = std::chrono::steady_clock;

    explicit SensorManager(std::chrono::microseconds period)
        : period_(period) {}

    bool addSensor(ISensor* s);
    bool initAll();
    void tick();

    // Drain samples (non-real-time side)
    bool popSample(std::size_t sensor_index, SensorSample& out);

    std::size_t sensorCount() const { return count_; }
    const char* sensorName(std::size_t idx) const { return sensors_[idx]->name(); }

private:
    std::chrono::microseconds period_;

    std::array<ISensor*, 8> sensors_{};
    std::size_t count_ = 0;

    // One queue per sensor (static allocation)
    std::array<RingBuffer<SensorSample, 64>, 8> queues_{};
};
