cmake_minimum_required(VERSION 3.16)
project(day02_sensor_pipeline CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sensor_pipeline
    main.cpp
    src/SensorManager.cpp
    src/FakeImuSensor.cpp
    src/FakeThermoSensor.cpp
)

target_include_directories(sensor_pipeline PRIVATE include)
target_compile_options(sensor_pipeline PRIVATE -O2 -Wall -Wextra -Wpedantic)
