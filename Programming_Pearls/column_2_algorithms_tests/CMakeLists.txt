cmake_minimum_required(VERSION 3.3)

project(column_2_algorithms)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runRotateTests
        rotate_test.cpp)

target_link_libraries(runRotateTests gtest gtest_main)
