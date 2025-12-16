#pragma once
#include <cstdint>

struct SensorSample {
    std::uint64_t t_us = 0;     // timestamp (microseconds, monotonic)
    float ax = 0, ay = 0, az = 0; // example IMU accel
    float gx = 0, gy = 0, gz = 0; // example IMU gyro

    float temp_c = 0.0f; // temperature
};
