cmake_minimum_required(VERSION 3.16)
project(day03_simple_inference CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(simple_inference
    main.cpp
    src/FeatureExtractor.cpp
    src/ThresholdDetector.cpp
    ../day02_sensor_pipeline/src/SensorManager.cpp
    ../day02_sensor_pipeline/src/FakeImuSensor.cpp
    ../day02_sensor_pipeline/src/FakeThermoSensor.cpp
)

target_include_directories(simple_inference PRIVATE
    include
    ../day02_sensor_pipeline/include
)

target_compile_options(simple_inference PRIVATE -O2 -Wall -Wextra -Wpedantic)
