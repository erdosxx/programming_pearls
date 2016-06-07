cmake_minimum_required(VERSION 3.3)

project(Ch10_Algorithm_Design)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runAlgorithmDesignTests
        algorithm_design_test.cpp)


target_link_libraries(runAlgorithmDesignTests gtest gtest_main)