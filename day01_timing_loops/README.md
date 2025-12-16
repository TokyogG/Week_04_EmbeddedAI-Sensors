### Timing Results (Pi 5, Linux, 50 Hz loop)

- Period: 20,000 µs (50 Hz)
- Simulated work: 2,000 µs
- Mean lateness: 60 µs
- Std dev: 115 µs
- Max lateness: 2,645 µs
- Overruns: 0 / 500 cycles

**Interpretation:** Average timing is stable (~60 µs late), but Linux scheduling can introduce occasional ms-scale jitter (2.6 ms worst-case observed). MCU timers/RTOS tasks are designed to reduce this unpredictability.

### Jitter Observations

Two back-to-back runs on the same system produced very different worst-case behavior:

| Run | Mean | Max | Std Dev |
|----|-----|-----|--------|
| Run A | ~60 µs | 2.6 ms | 115 µs |
| Run B | ~53 µs | 100 µs | 4 µs |

**Conclusion:** Linux scheduling can appear highly stable but offers no hard real-time guarantees. Worst-case latency must be assumed, not inferred from averages.
