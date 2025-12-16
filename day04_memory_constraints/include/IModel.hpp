#pragma once
#include "ModelIO.hpp"

class IModel {
public:
    virtual ~IModel() = default;
    virtual bool init() = 0;
    virtual bool run(const ModelInputInt8& in, ModelOutput& out) = 0;
    virtual const char* name() const = 0;
};
