#pragma once
#include <array>
#include <cstdint>

constexpr std::size_t kNumFeatures = 2; // accel_dev, temp_c
constexpr std::size_t kNumClasses  = 2; // normal, anomaly

struct ModelInputInt8 {
    std::array<std::int8_t, kNumFeatures> x{};
};

struct ModelOutput {
    // simple scores/logits (not softmax)
    std::array<float, kNumClasses> y{};
};
