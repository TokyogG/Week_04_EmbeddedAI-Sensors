#include "ThresholdDetector.hpp"

ThresholdDetector::ThresholdDetector(float accel_thresh, float temp_thresh)
    : accel_thresh_(accel_thresh),
      temp_thresh_(temp_thresh) {}

InferenceResult ThresholdDetector::infer(const FeatureVector& fv) const {
    if (fv.accel_mag > accel_thresh_) {
        return InferenceResult::Anomaly;
    }
    if (fv.temp_c > temp_thresh_) {
        return InferenceResult::Anomaly;
    }
    return InferenceResult::Normal;
}
