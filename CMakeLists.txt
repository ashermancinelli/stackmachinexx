cmake_minimum_required (VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(sm CXX)

set(GTEST_LINKED_AS_SHARED_LIBRARY OFF)
set(FMT_SHARED OFF)
set(SPDLOG_SHARED_LIB OFF)
find_package(cxxopts CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()

add_test(NAME NoArgs COMMAND $<TARGET_FILE:sm>)
add_test(NAME Help COMMAND $<TARGET_FILE:sm> --help)
# add_test(NAME StackMachine_Unit COMMAND $<TARGET_FILE:testStackMachine>)
add_test(NAME StackHandle_Unit COMMAND $<TARGET_FILE:testStackHandle>)
