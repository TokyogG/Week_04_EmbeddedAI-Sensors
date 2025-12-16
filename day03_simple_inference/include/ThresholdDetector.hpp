#pragma once
#include "InferenceTypes.hpp"

class ThresholdDetector {
public:
    ThresholdDetector(float accel_thresh, float temp_thresh);

    InferenceResult infer(const FeatureVector& fv) const;

private:
    float accel_thresh_;
    float temp_thresh_;
};
