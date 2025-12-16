#pragma once
#include "IModel.hpp"

class DummyModel : public IModel {
public:
    bool init() override { return true; }
    bool run(const ModelInputInt8& in, ModelOutput& out) override;
    const char* name() const override { return "DummyModel(int8)"; }
};
