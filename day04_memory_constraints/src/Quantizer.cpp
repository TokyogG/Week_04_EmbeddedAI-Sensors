#include "Quantizer.hpp"
#include <cmath>

std::int8_t Quantizer::clamp_int8(int v) {
    if (v < -128) return static_cast<std::int8_t>(-128);
    if (v > 127)  return static_cast<std::int8_t>(127);
    return static_cast<std::int8_t>(v);
}

ModelInputInt8 Quantizer::quantize(const FeatureVector& fv) const {
    ModelInputInt8 out{};

    auto q = [](float x, QuantParams p) -> std::int8_t {
        const float qf = (x / p.scale) + static_cast<float>(p.zero);
        const int qi = static_cast<int>(std::lround(qf));
        return Quantizer::clamp_int8(qi);
    };

    // Feature order must match model expectation
    out.x[0] = q(fv.accel_mag, accel_q_); // accel_dev (|‖a‖-g|)
    out.x[1] = q(fv.temp_c,    temp_q_);  // temperature
    return out;
}
