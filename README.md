# **Week 04 — Embedded AI & Sensor Pipelines (C++ → TinyML Ready)**

*Part of the 16-Week Edge AI Engineering Bootcamp*

Week 04 builds on the C/C++ foundations from Week 03 and begins transitioning toward **embedded AI execution**.
The focus is on **sensor pipelines, deterministic timing, and lightweight inference logic** that will later map cleanly onto microcontrollers (STM32) and TinyML runtimes.

---

## 🚀 **Weekly Objectives**

By the end of Week 04, you should be able to:

### **Embedded Systems**

* Design deterministic sensor loops (fixed-rate execution)
* Reason about timing, buffering, and latency
* Structure multi-sensor pipelines in C/C++

### **Embedded AI Foundations**

* Implement simple anomaly detection / inference logic in C++
* Understand where ML fits vs classic DSP / threshold logic
* Prepare code for future MCU deployment (no dynamic allocation in hot paths)

### **Performance & Constraints**

* Measure execution time at millisecond and microsecond scales
* Track memory usage and binary size
* Reason about tradeoffs: accuracy vs latency vs power

---

## 📁 **Folder Structure (Planned)**

```text
Week_04_EmbeddedAI-Sensors/
│
├── day01_timing_loops/
│   ├── fixed_rate_loop.cpp
│   ├── jitter_measure.cpp
│   └── CMakeLists.txt
│
├── day02_sensor_pipeline/
│   ├── sensor_manager.cpp
│   ├── sensor_manager.h
│   ├── mpu6050_driver.cpp
│   └── CMakeLists.txt
│
├── day03_simple_inference/
│   ├── threshold_detector.cpp
│   ├── threshold_detector.h
│   ├── anomaly_demo.cpp
│   └── CMakeLists.txt
│
├── day04_memory_constraints/
│   ├── static_vs_dynamic.cpp
│   ├── stack_usage.cpp
│   └── notes.md
│
└── day05_integration_summary/
```

> ⚠️ Folder names are **tentative** — they may evolve as implementations solidify.

---

## 🟦 **Day 01 — Deterministic Timing & Fixed-Rate Loops**

### Focus

* Fixed-rate execution (e.g. 50 Hz, 100 Hz)
* `sleep_until` vs `sleep_for`
* Measuring jitter and drift
* Why deterministic timing matters for embedded AI

### Expected Outcomes

* Stable loop timing with quantified jitter
* Understanding of Linux scheduling limits vs MCU behavior

---

## 🟧 **Day 02 — Sensor Pipeline Architecture**

### Focus

* Managing multiple sensors cleanly
* Separating acquisition, processing, and output
* Avoiding tight coupling between drivers and logic

### Expected Outcomes

* Modular sensor pipeline design
* Clean interfaces suitable for MCU porting

---

## 🟩 **Day 03 — Simple Inference & Anomaly Detection**

### Focus

* Threshold-based anomaly detection
* When classical logic beats ML
* Framing the problem for later TinyML replacement

### Expected Outcomes

* Working anomaly detector in C++
* Clear data path: sensor → features → decision

---

## 🟪 **Day 04 — Memory & Embedded Constraints**

### Focus

* Static vs dynamic allocation
* Stack usage analysis
* Binary size awareness
* Why “it runs on a Pi” is not enough

### Expected Outcomes

* Code that avoids heap allocation in hot paths
* Awareness of MCU-level constraints before touching STM32

---

## 🟥 **Day 05 — Integration & Weekly Summary**

### Focus

* Integrating timing, sensors, and inference
* Measuring end-to-end latency
* Documenting tradeoffs and lessons learned

### Expected Outcomes

* End-to-end embedded-style pipeline
* Clear preparation for:

  * Week 05 (Quantization concepts)
  * Week 13 (STM32 + TinyML)

---

## 📊 **Metrics to Track (Week 04)**

| Metric              | Target / Observation     |
| ------------------- | ------------------------ |
| Loop rate stability | ±1–2 ms jitter           |
| Sensor read latency | measured                 |
| Inference latency   | measured                 |
| Heap allocations    | ideally zero in hot path |
| Binary size         | tracked (baseline)       |

---

## ✅ **Week 04 Outcome**

By the end of Week 04, you should have:

* A deterministic, modular C++ sensor pipeline
* Lightweight inference logic suitable for edge deployment
* A clear mental model of **what must change** when moving from Pi → MCU
* Code that is structurally ready for TinyML, even if ML is not yet used

---

## 🔜 **What This Enables Next**

Week 04 sets up:

* **Week 05:** Quantization & model constraints
* **Week 06+:** Accelerator deployment (Hailo / NPU)
* **Week 13:** STM32 + CMSIS-NN + TFLite Micro

---