#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <thread>
#include <limits>

using SteadyClock = std::chrono::steady_clock;

int main() {
    constexpr int N = 500;                                // number of cycles
    constexpr auto PERIOD = std::chrono::milliseconds(20); // 50 Hz
    constexpr auto WORK = std::chrono::milliseconds(2);    // simulated work

    auto next_tick = SteadyClock::now();

    long long min_us = std::numeric_limits<long long>::max();
    long long max_us = std::numeric_limits<long long>::min();
    long double sum_us = 0.0L;
    long double sumsq_us = 0.0L;

    int overruns = 0;

    for (int i = 0; i < N; ++i) {
        auto now = SteadyClock::now();
        auto lateness = now - next_tick;
        auto lateness_us = std::chrono::duration_cast<std::chrono::microseconds>(lateness).count();

        // Track stats
        if (lateness_us < min_us) min_us = lateness_us;
        if (lateness_us > max_us) max_us = lateness_us;
        sum_us += static_cast<long double>(lateness_us);
        sumsq_us += static_cast<long double>(lateness_us) * static_cast<long double>(lateness_us);

        // Overrun means we woke up after the *next* period would have started
        if (lateness > PERIOD) {
            overruns++;
        }

        // Simulated work
        std::this_thread::sleep_for(WORK);

        next_tick += PERIOD;
        std::this_thread::sleep_until(next_tick);
    }

    long double mean = sum_us / N;
    long double var = (sumsq_us / N) - (mean * mean);
    if (var < 0) var = 0; // numerical safety
    long double stddev = std::sqrt(static_cast<double>(var));

    std::cout << "---- Jitter Summary (50 Hz target) ----\n";
    std::cout << "cycles:   " << N << "\n";
    std::cout << "period:   " << std::chrono::duration_cast<std::chrono::microseconds>(PERIOD).count() << " us\n";
    std::cout << "work:     " << std::chrono::duration_cast<std::chrono::microseconds>(WORK).count() << " us\n";
    std::cout << "min:      " << min_us << " us\n";
    std::cout << "max:      " << max_us << " us\n";
    std::cout << "mean:     " << static_cast<long long>(mean) << " us\n";
    std::cout << "stddev:   " << static_cast<long long>(stddev) << " us\n";
    std::cout << "overruns: " << overruns << "\n";

    return 0;
}