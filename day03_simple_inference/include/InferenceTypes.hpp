#pragma once
#include <cstdint>

struct FeatureVector {
    std::uint64_t t_us = 0;
    float accel_mag = 0.0f;
    float temp_c = 0.0f;
};

enum class InferenceResult {
    Normal,
    Anomaly
};
