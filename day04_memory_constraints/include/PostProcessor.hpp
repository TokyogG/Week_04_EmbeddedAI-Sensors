#pragma once
#include "ModelIO.hpp"
#include "InferenceTypes.hpp"

class PostProcessor {
public:
    InferenceResult decide(const ModelOutput& out) const {
        // class 1 = anomaly
        return (out.y[1] > out.y[0]) ? InferenceResult::Anomaly : InferenceResult::Normal;
    }
};
