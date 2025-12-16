#include "FeatureExtractor.hpp"
#include <cmath>

FeatureVector FeatureExtractor::extract(const SensorSample& s) const {
    FeatureVector fv{};
    fv.t_us = s.t_us;

    // Acceleration magnitude (m/s^2)
    const float mag = std::sqrt(
        s.ax * s.ax +
        s.ay * s.ay +
        s.az * s.az
    );

    // Feature = deviation from gravity (shock/vibration proxy)
    constexpr float G = 9.81f;
    fv.accel_mag = std::fabs(mag - G);

    // Temperature passthrough
    fv.temp_c = s.temp_c;
    return fv;
}
