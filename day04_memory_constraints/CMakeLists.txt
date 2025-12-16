cmake_minimum_required(VERSION 3.16)
project(day04_memory_constraints CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(model_ready
    main.cpp
    src/Quantizer.cpp
    src/DummyModel.cpp

    # Reuse Day03 feature extraction
    ../day03_simple_inference/src/FeatureExtractor.cpp

    # Reuse Day02 sensor pipeline
    ../day02_sensor_pipeline/src/SensorManager.cpp
    ../day02_sensor_pipeline/src/FakeImuSensor.cpp
    ../day02_sensor_pipeline/src/FakeThermoSensor.cpp
)

target_include_directories(model_ready PRIVATE
    include
    ../day03_simple_inference/include
    ../day02_sensor_pipeline/include
)

target_compile_options(model_ready PRIVATE -O2 -Wall -Wextra -Wpedantic)
