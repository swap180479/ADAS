cmake_minimum_required(VERSION 3.16)
project(ADAS_AEB_Sample LANGUAGES C)

add_library(aeb STATIC src/aeb_controller.c)
target_include_directories(aeb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(aeb PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED YES)
