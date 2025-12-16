#include "DummyModel.hpp"
#include <cstdlib>
#include <cmath>

bool DummyModel::run(const ModelInputInt8& in, ModelOutput& out) {
    const int a = static_cast<int>(in.x[0]); // accel_dev_q (symmetric)
    const int t = static_cast<int>(in.x[1]); // temp_q centered around ~25C (0 ~= 25C)

    // Deadbands to avoid flipping on tiny noise
    const int a_deadband = 2;   // ignore small accel_dev
    const int t_deadband = 3;   // ignore +/-0.2C-ish if scale=0.1

    const float a_term = (std::abs(a) > a_deadband) ? (0.25f * float(std::abs(a) - a_deadband)) : 0.0f;
    const float t_term = (std::abs(t) > t_deadband) ? (0.08f * float(std::abs(t) - t_deadband)) : 0.0f;

    // anomaly score from both terms
    const float anomaly = a_term + t_term;
    const float normal  = -anomaly;

    out.y[0] = normal;
    out.y[1] = anomaly;
    return true;
}
