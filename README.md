# Week 04 — Embedded AI & Sensor Pipelines

*Part of the 16‑Week Edge AI Engineering Bootcamp*

---

## Overview

Week 04 transitions from **embedded C/C++ fundamentals** into **edge‑AI execution architecture**.
The emphasis is not on training models, but on building the **runtime systems** that make AI *deployable* under real embedded constraints:

* Deterministic timing
* Bounded memory usage
* Modular sensor pipelines
* Event‑driven inference
* INT8, model‑ready execution paths

By the end of the week, the system is architecturally prepared to integrate real accelerators (Hailo, CMSIS‑NN, TFLite Micro) **without redesigning the pipeline**.

---

## Weekly Objectives

By the end of Week 04, you should be able to:

### Embedded Systems

* Design fixed‑rate execution loops and quantify jitter
* Reason about latency, buffering, and scheduling
* Structure multi‑sensor pipelines in modern C++

### Embedded AI Foundations

* Implement lightweight anomaly detection in C++
* Understand where classical logic fits vs ML
* Prepare inference paths for MCU / NPU deployment

### Performance & Constraints

* Measure execution time at µs–ms scale
* Track memory usage and avoid dynamic allocation in hot paths
* Reason about accuracy vs latency vs memory trade‑offs

---

## Folder Structure (Final)

```
Week_04_EmbeddedAI-Sensors/
├── day01_timing_loops
├── day02_sensor_pipeline
├── day03_simple_inference
├── day04_memory_constraints
├── day05_integration_summary
└── README.md
```

Each day builds directly on the previous one.

---

## Day 01 — Deterministic Timing & Jitter

**Focus**

* Fixed‑rate loops (50 Hz)
* `sleep_until` vs `sleep_for`
* Measuring lateness and jitter
* Why worst‑case latency matters

**Key Results (Pi 5, Linux, 50 Hz)**

* Period: 20 000 µs
* Mean lateness: ~50–60 µs
* Worst‑case lateness: up to ~2.6 ms
* Overruns: 0 / 500 cycles

**Takeaway**
Average timing can look stable, but Linux provides **no hard real‑time guarantees**. Embedded systems must be designed assuming worst‑case behavior.

---

## Day 02 — Sensor Pipeline Architecture

**Focus**

* Clean multi‑sensor design
* Decoupling acquisition from processing
* Embedded‑style interfaces

**Key Results**

* Implemented a central `SensorManager` with a common `ISensor` interface
* Added per‑sensor static RingBuffers to decouple real‑time acquisition from slower logic
* Verified multi‑sensor sampling within the same tick (fusion‑ready timestamps)
* Preserved deterministic timing as sensors scaled

**Outcome**
A modular, heap‑free sensor pipeline suitable for MCU deployment and future sensor fusion.

---

## Day 03 — Simple Inference & Anomaly Detection

**Focus**

* Lightweight inference without ML
* Event‑driven decisions
* Framing problems for later TinyML replacement

**Key Results**

* Feature extraction:

  * Acceleration deviation from gravity (`|‖a‖ − 9.81|`)
  * Temperature
* Threshold‑based inference detecting:

  * Mechanical shock
  * Thermal drift
* Event‑driven logging (state changes only)

**Outcome**
A clean `sensor → features → decision` pipeline producing stable NORMAL ↔ ANOMALY transitions.

---

## Day 04 — Memory Constraints & Model‑Ready Inference

**Focus**

* Embedded memory constraints
* Model‑shaped inference paths
* Preparing for real accelerators

**Key Concepts**

* Fixed‑size tensors (`std::array`)
* Explicit INT8 quantization
* Stable model input/output contracts
* `IModel` runtime interface
* Deterministic post‑processing

**Pipeline**

```
SensorManager → RingBuffer → FeatureExtractor → Quantizer(INT8)
→ Model Interface → PostProcessor → Event
```

**Outcome**
A model‑ready INT8 inference pipeline with deterministic memory usage, ready to swap in Hailo / CMSIS‑NN / TFLite Micro.

---

## Day 05 — Integration & Weekly Wrap‑Up

**Focus**

* One‑command build and execution
* End‑to‑end verification
* Engineering narrative

**Key Results**

* Single integration build compiling all days
* Verified full path: timing → sensors → inference → INT8 model execution
* Produced a portfolio‑ready embedded AI system

---

## Week 04 Results Summary

* Deterministic 50 Hz loops with measured jitter
* Modular SensorManager + RingBuffer pipeline
* Event‑driven anomaly detection
* INT8, model‑ready inference under memory constraints
* Architecture prepared for real NPUs and MCUs

---

## Why This Matters

Edge AI systems are shaped by **constraints**, not models alone:

* Memory limits force INT8 quantization and fixed tensor shapes
* Timing constraints require event‑driven design
* Clean pipelines enable accelerator portability

These patterns mirror production systems in robotics, rail safety, industrial monitoring, and automotive domains.

---

## What Comes Next

* **Week 05:** Quantization fundamentals & real models (e.g., MobileNet INT8)
* **Week 06+:** ONNX → Hailo deployment
* **Week 13:** STM32 + CMSIS‑NN + TinyML

Week 04 provides the execution backbone for everything that follows.
