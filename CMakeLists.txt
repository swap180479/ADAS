cmake_minimum_required(VERSION 3.16)
project(ADAS_AEB_Sample LANGUAGES C CXX)

add_library(aeb STATIC src/aeb_controller.c)
target_include_directories(aeb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(aeb PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED YES)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(aeb_tests tests/test_aeb_controller.cpp)
    target_compile_features(aeb_tests PRIVATE cxx_std_17)
    target_link_libraries(aeb_tests PRIVATE aeb GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(aeb_tests)
endif()
