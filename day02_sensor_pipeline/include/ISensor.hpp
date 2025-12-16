#pragma once
#include "SensorTypes.hpp"

class ISensor {
public:
    virtual ~ISensor() = default;

    virtual bool init() = 0;                 // hardware init
    virtual bool read(SensorSample& out) = 0; // acquire one sample
    virtual const char* name() const = 0;
};
