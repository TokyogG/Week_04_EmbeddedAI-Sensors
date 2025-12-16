#include <chrono>
#include <thread>
#include <iostream>
#include <cstdint>

#include "SensorManager.hpp"
#include "FakeImuSensor.hpp"
#include "FakeThermoSensor.hpp"
#include "FeatureExtractor.hpp"
#include "ThresholdDetector.hpp"

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

    // Thresholds tuned for our synthetic signals:
    // - accel_dev spikes when shock is injected (counter % 50 == 0)
    // - temp crosses 25.35 occasionally due to sine wave
    ThresholdDetector detector(
        /* accel_dev threshold */ 1.0f,
        /* temp threshold      */ 25.35f
    );

    auto next_tick = SensorManager::SteadyClock::now() + PERIOD;

    float latest_accel_dev = 0.0f;
    float latest_temp_c = 0.0f;
    std::uint64_t latest_imu_t = 0;
    std::uint64_t latest_temp_t = 0;
    bool have_imu = false;
    bool have_temp = false;

    InferenceResult last = InferenceResult::Normal;

    for (int i = 0; i < 400; ++i) { // run longer to see events
        mgr.tick();

        // Drain all samples and update latest state
        for (std::size_t s = 0; s < mgr.sensorCount(); ++s) {
            SensorSample sample{};
            while (mgr.popSample(s, sample)) {
                auto fv = extractor.extract(sample);

                // IMU sample has accel_dev > ~0, thermo sample has accel_dev ~|0 - 9.81|? Actually ax/ay/az=0 -> mag=0 -> dev=9.81,
                // so we use a robust classifier based on temperature being nonzero for thermo.
                // Thermo sample always provides temp; IMU sample provides temp=0.

                if (fv.temp_c > 0.1f) {
                    latest_temp_c = fv.temp_c;
                    latest_temp_t = fv.t_us;
                    have_temp = true;
                } else {
                    // Treat as IMU sample
                    latest_accel_dev = fv.accel_mag;
                    latest_imu_t = fv.t_us;
                    have_imu = true;
                }
            }
        }

        if (have_imu && have_temp) {
            FeatureVector fused{};
            fused.accel_mag = latest_accel_dev; // this is accel deviation feature
            fused.temp_c = latest_temp_c;
            fused.t_us = (latest_imu_t > latest_temp_t) ? latest_imu_t : latest_temp_t;

            auto result = detector.infer(fused);

            // Event-driven logging: only print on state changes
            if (result != last) {
                std::cout << "EVENT t_us=" << fused.t_us
                          << " accel_dev=" << fused.accel_mag
                          << " temp=" << fused.temp_c
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
