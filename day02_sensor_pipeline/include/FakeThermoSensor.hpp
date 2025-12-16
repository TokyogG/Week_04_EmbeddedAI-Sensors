#pragma once
#include "ISensor.hpp"
#include <cstdint>

class FakeThermoSensor : public ISensor {
public:
    bool init() override;
    bool read(SensorSample& out) override;
    const char* name() const override { return "FakeThermo"; }

private:
    std::uint64_t counter_ = 0;
};
