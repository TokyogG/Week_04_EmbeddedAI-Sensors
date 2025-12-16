#include <chrono>
#include <thread>
#include <iostream>
#include <cstdint>

#include "SensorManager.hpp"
#include "FakeImuSensor.hpp"
#include "FakeThermoSensor.hpp"
#include "FeatureExtractor.hpp"
#include "InferenceTypes.hpp"

#include "Quantizer.hpp"
#include "DummyModel.hpp"
#include "PostProcessor.hpp"

int main() {
    using namespace std::chrono;

    constexpr auto PERIOD = milliseconds(20); // 50 Hz
    SensorManager mgr(duration_cast<microseconds>(PERIOD));

    FakeImuSensor imu;
    FakeThermoSensor thermo;

    mgr.addSensor(&imu);
    mgr.addSensor(&thermo);

    if (!mgr.initAll()) {
        std::cerr << "Sensor init failed\n";
        return 1;
    }

    FeatureExtractor extractor;

    // Quantization params (chosen for our toy feature ranges)
    // accel_dev: typical ~0..3+   -> scale 0.05 gives ~0..60 int8 range
    // temp_c:    typical ~24..26 -> scale 0.1 gives ~240..260 which will saturate,
    //          so we use a centered zero-point: zero = -250 means 25.0C maps near 0.
    Quantizer quant(
        QuantParams{0.05f, 0},     // accel_dev
        QuantParams{0.1f, -250}    // temp_c (center around ~25C)
    );

    DummyModel model;
    PostProcessor post;

    if (!model.init()) {
        std::cerr << "Model init failed\n";
        return 1;
    }

    auto next_tick = SensorManager::SteadyClock::now() + PERIOD;

    // Fused state (latest values)
    float latest_accel_dev = 0.0f;
    float latest_temp_c = 0.0f;
    std::uint64_t latest_imu_t = 0;
    std::uint64_t latest_temp_t = 0;
    bool have_imu = false;
    bool have_temp = false;

    InferenceResult last = InferenceResult::Normal;

    for (int i = 0; i < 400; ++i) {
        mgr.tick();

        // Drain buffers and update latest values
        for (std::size_t s = 0; s < mgr.sensorCount(); ++s) {
            SensorSample sample{};
            while (mgr.popSample(s, sample)) {
                auto fv = extractor.extract(sample);

                // Thermo samples have temp set; IMU samples have temp=0
                if (fv.temp_c > 0.1f) {
                    latest_temp_c = fv.temp_c;
                    latest_temp_t = fv.t_us;
                    have_temp = true;
                } else {
                    latest_accel_dev = fv.accel_mag; // accel_dev feature from Day03 extractor
                    latest_imu_t = fv.t_us;
                    have_imu = true;
                }
            }
        }

        if (have_imu && have_temp) {
            FeatureVector fused{};
            fused.accel_mag = latest_accel_dev; // accel_dev
            fused.temp_c = latest_temp_c;
            fused.t_us = (latest_imu_t > latest_temp_t) ? latest_imu_t : latest_temp_t;

            // float -> int8 tensor
            ModelInputInt8 xin = quant.quantize(fused);

            // "model" inference
            ModelOutput yout{};
            model.run(xin, yout);

            // postprocess -> decision
            auto result = post.decide(yout);

            // event-driven output
            if (result != last) {
                // --- DEBUG / EXPLANATION ONLY ---
                const float accel_deq = float(xin.x[0]) * 0.05f;                 // scale
                const float temp_deq  = (float(xin.x[1]) - (-250)) * 0.1f;       // (q - zero) * scale
                // --------------------------------

                std::cout << "EVENT t_us=" << fused.t_us
                        << " accel_dev=" << fused.accel_mag
                        << " temp=" << fused.temp_c
                        << " | x_int8=[" << static_cast<int>(xin.x[0]) << ", "
                        << static_cast<int>(xin.x[1]) << "]"
                        << " | deq=[" << accel_deq << ", " << temp_deq << "]"
                        << " | y=[" << yout.y[0] << ", " << yout.y[1] << "]"
                        << " -> " << (result == InferenceResult::Normal ? "NORMAL" : "ANOMALY")
                        << "\n";

                last = result;
            }

        }

        std::this_thread::sleep_until(next_tick);
        next_tick += PERIOD;
    }
    return 0;
}
