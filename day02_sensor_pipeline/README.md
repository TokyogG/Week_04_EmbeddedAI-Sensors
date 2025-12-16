Day 02 — SensorManager Architecture & Buffered Pipelines
🎯 Objective

Design a modular, deterministic sensor pipeline in C++ that cleanly separates:

timing

sensor acquisition

buffering

downstream processing

This structure mirrors real embedded systems and prepares the codebase for MCU deployment and TinyML integration later in the program.

🧠 Key Concepts Introduced

Sensor abstraction via a common interface (ISensor)

Central orchestration with SensorManager

Deterministic fixed-rate execution (50 Hz)

Separation of real-time and non-real-time work

Static memory allocation (embedded-friendly)

🏗️ Architecture Overview
Fixed-rate loop (50 Hz)
        │
        ▼
  SensorManager::tick()
        │
        ├─ read Sensor A (IMU)
        ├─ read Sensor B (Thermo)
        │
        ▼
   Per-sensor RingBuffers
        │
        ▼
 Non-real-time processing
 (logging / inference / features)


Each sensor implements the same ISensor interface, allowing the manager to scale from one sensor to many without changing core logic.

📦 Sensor Interfaces

All sensors implement:

bool init();
bool read(SensorSample& out);
const char* name() const;


This allows:

real hardware drivers later (MPU6050, thermistors, GNSS)

fake sensors for testing on desktop

identical code paths on Pi and MCU

⏱️ Deterministic Timing

Loop rate: 50 Hz (20 ms period)

Sampling for all sensors occurs in the same tick

Identical timestamps across sensors enable future sensor fusion

Observed output confirms consistent ~20 ms spacing between samples.

🔄 Buffering with RingBuffers (Bonus)

To avoid doing slow operations (e.g., printing, logging) in the time-critical path, each sensor writes samples into a fixed-size RingBuffer.

Pipeline:

Sensor → RingBuffer → Processing / Logging

Why RingBuffers are common in embedded systems

O(1) push/pop

Fixed memory usage (no heap)

Prevents data loss under bursty workloads

Widely used for UART RX, IMU streams, audio, CAN, DMA pipelines

Design choice

When full, the buffer overwrites the oldest sample, prioritizing fresh data — a common real-time policy.

🧪 Validation Results

Two sensors sampled in the same tick share the same timestamp

Deterministic timing preserved after adding buffering

No dynamic allocation in the hot path

Architecture scales cleanly from 1 → N sensors

Example output:

[FakeIMU]    t_us=... ax=0.05 ay=0.02 az=9.81
[FakeThermo] t_us=... temp_c=25.12

✅ Day 02 Outcome

By the end of Day 02, we have:

A reusable SensorManager

A clean multi-sensor architecture

A buffered data path suitable for real-time systems

Code that is structurally ready for:

threshold-based inference (Day 03)

TinyML integration (later weeks)

MCU/RTOS deployment