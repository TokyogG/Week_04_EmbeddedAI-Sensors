#pragma once
#include "SensorTypes.hpp"
#include "InferenceTypes.hpp"

class FeatureExtractor {
public:
    FeatureVector extract(const SensorSample& sample) const;
};
