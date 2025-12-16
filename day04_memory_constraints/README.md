## Day 04 — Memory Constraints & Model-Ready Inference

Today converts the Day 03 threshold pipeline into a **model-ready** inference path under embedded constraints:

- **Fixed-size tensors** (`std::array`) for deterministic memory
- **INT8 quantization** (float features → int8 model input)
- `IModel` interface + `DummyModel` runner (drop-in replacement for real runtimes later)
- `PostProcessor` to map model outputs → NORMAL/ANOMALY
- Event-driven logging (state transitions only)

**Pipeline**
SensorManager → RingBuffer → FeatureExtractor → Quantizer(INT8) → ModelRunner → PostProcess → Event
