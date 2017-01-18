cmake_minimum_required(VERSION 3.3)

project(State)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runStateTests
        state_test.cpp)

target_link_libraries(runStateTests gtest gtest_main)