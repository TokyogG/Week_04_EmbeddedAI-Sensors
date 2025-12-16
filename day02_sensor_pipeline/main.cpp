#include <chrono>
#include <thread>
#include <iostream>

#include "SensorManager.hpp"
#include "FakeImuSensor.hpp"
#include "FakeThermoSensor.hpp"

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

    auto next_tick = SensorManager::SteadyClock::now() + PERIOD;
    std::uint64_t printed = 0;

    for (int i = 0; i < 200; ++i) {
        mgr.tick(); // RT-ish path: read + enqueue

        // Non-RT path: drain queues and print
        for (std::size_t s = 0; s < mgr.sensorCount(); ++s) {
            SensorSample sample{};
            while (mgr.popSample(s, sample)) {
                if (s == 0) { // FakeIMU
                    std::cout << "[" << mgr.sensorName(s) << "] t_us=" << sample.t_us
                              << " ax=" << sample.ax << " ay=" << sample.ay << " az=" << sample.az
                              << "\n";
                } else {      // FakeThermo
                    std::cout << "[" << mgr.sensorName(s) << "] t_us=" << sample.t_us
                              << " temp_c=" << sample.temp_c
                              << "\n";
                }
                printed++;
                if (printed >= 20) break; // keep output manageable
            }
            if (printed >= 20) break;
        }

        std::this_thread::sleep_until(next_tick);
        next_tick += PERIOD;
    }

    return 0;
}
