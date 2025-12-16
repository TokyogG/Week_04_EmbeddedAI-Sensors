#include "FakeImuSensor.hpp"
#include <chrono>

bool FakeImuSensor::init() {
    counter_ = 0;
    return true;
}

bool FakeImuSensor::read(SensorSample& out) {
    auto now = std::chrono::steady_clock::now().time_since_epoch();
    out.t_us = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(now).count()
    );

    // Baseline: mostly stable "resting" IMU
    out.ax = 0.01f * static_cast<float>(counter_);
    out.ay = 0.02f;
    out.az = 9.81f;

    // Inject a "shock" once per second (50 Hz loop -> every 50 samples)
    if (counter_ % 50 == 0) {
        out.az += 3.0f; // bump adds ~3 m/s^2, easy to detect
    }

    out.gx = 0.0f;
    out.gy = 0.0f;
    out.gz = 0.001f * static_cast<float>(counter_);

    counter_++;
    return true;
}
