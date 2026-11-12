# ADAS — AEB Sample

Educational Automatic Emergency Braking (AEB) C/C++ sample for EmbeddedAuto AI ASPICE requirement-to-source-to-test workflows.

**Not production software. Not validated or certified for vehicle use.** This deliberately simplified example ignores sensor uncertainty, actuator timing, driver override, diagnostics, redundancy, and functional safety analysis.

## Layout
- `requirements/AEB_Requirements.md`: normative sample requirements and test vectors
- `include/aeb_controller.h`: public C API
- `src/aeb_controller.c`: implementation
- `tests/test_aeb_controller.cpp`: executable GoogleTests
- `CMakeLists.txt`: C11 library and C++17 tests

## Build and test
Requires CMake 3.16+, a C compiler, a C++17 compiler, and internet access for CMake FetchContent to download GoogleTest.

```sh
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

For library-only builds, use `-DBUILD_TESTING=OFF`.

## Simplified sample policy
Input distance is in metres and closing speed in metres/second. A closing speed of zero means no approach. For positive closing speed, time-to-collision (TTC) is distance / closing speed. Braking is requested when TTC is at most 2.0 seconds. Invalid or non-finite inputs return an error and never request braking. This behavior is **only a sample specification**; it is not a recommended automotive braking policy.
