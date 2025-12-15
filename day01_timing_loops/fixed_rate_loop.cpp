#include <chrono>
#include <iostream>
#include <thread>

using SteadyClock = std::chrono::steady_clock;

int main() {
    constexpr auto PERIOD = std::chrono::milliseconds(20); // 50 Hz

    auto next_tick = SteadyClock::now();

    for (int i = 0; i < 200; ++i) {
        auto now = SteadyClock::now();
        auto lateness = now - next_tick;

        std::cout << "Loop " << i
                  << " lateness (us): "
                  << std::chrono::duration_cast<std::chrono::microseconds>(lateness).count()
                  << "\n";

        // Simulated work
        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        next_tick += PERIOD;
        std::this_thread::sleep_until(next_tick);
    }

    return 0;
}