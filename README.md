# ADAS — AEB Sample Input Project

Educational Automatic Emergency Braking (AEB) C source project and requirements for exercising EmbeddedAuto AI ASPICE analysis and AI-driven test generation.

**This repository intentionally contains no pre-generated test cases, GoogleTest source, or SUT test adapter.** EmbeddedAuto AI ASPICE must derive test scenarios and executable tests from the supplied requirements and actual source code. If the available evidence is insufficient, the platform must report the affected test as blocked and explain the missing evidence rather than inventing behavior or placeholder tests.

**Not production software. Not validated or certified for vehicle use.** This deliberately simplified example ignores sensor uncertainty, actuator timing, driver override, diagnostics, redundancy, and functional safety analysis.

## Input project layout
- `requirements/AEB_Requirements.md`: sample requirements
- `include/aeb_controller.h`: public C API
- `src/aeb_controller.c`: implementation
- `CMakeLists.txt`: source-library build only

## Build source library
Requires CMake 3.16+ and a C compiler.

```sh
cmake -S . -B build
cmake --build build
```

## Simplified sample behavior
Input distance is in metres and closing speed in metres/second. A closing speed of zero means no approach. For positive closing speed, time-to-collision (TTC) is distance / closing speed. Braking is requested when TTC is at most 2.0 seconds. Invalid or non-finite inputs return an error. This behavior is **only a sample specification**; it is not a recommended automotive braking policy.
