cmake_minimum_required(VERSION 3.3)

project(column_8_algorithm_design_techniques)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runMaxSumTests
        maxsum_test.cpp)

target_link_libraries(runMaxSumTests gtest gtest_main)
