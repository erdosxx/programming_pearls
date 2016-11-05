cmake_minimum_required(VERSION 3.3)

project(Ch1_Getting_Ready)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runGettingReadyTests
        getting_ready_test.cpp)

target_link_libraries(runGettingReadyTests gtest gtest_main)