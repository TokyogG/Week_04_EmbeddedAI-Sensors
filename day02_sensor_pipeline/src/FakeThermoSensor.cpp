#include "FakeThermoSensor.hpp"
#include <chrono>
#include <cmath>

bool FakeThermoSensor::init() {
    counter_ = 0;
    return true;
}

bool FakeThermoSensor::read(SensorSample& out) {
    auto now = std::chrono::steady_clock::now().time_since_epoch();
    out.t_us = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(now).count()
    );

    // Simple synthetic temperature signal: ~25C with a gentle wave
    const float base = 25.0f;
    const float wave = 0.5f * std::sin(static_cast<float>(counter_) * 0.05f);
    out.temp_c = base + wave;

    counter_++;
    return true;
}
