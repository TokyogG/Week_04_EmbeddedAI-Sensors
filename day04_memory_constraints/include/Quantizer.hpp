#pragma once
#include <cstdint>
#include "InferenceTypes.hpp"
#include "ModelIO.hpp"

struct QuantParams {
    float scale = 0.1f; // float ≈ int8 * scale
    int   zero  = 0;    // symmetric by default
};

class Quantizer {
public:
    Quantizer(QuantParams accel_q, QuantParams temp_q)
        : accel_q_(accel_q), temp_q_(temp_q) {}

    ModelInputInt8 quantize(const FeatureVector& fv) const;

private:
    QuantParams accel_q_;
    QuantParams temp_q_;

    static std::int8_t clamp_int8(int v);
};
