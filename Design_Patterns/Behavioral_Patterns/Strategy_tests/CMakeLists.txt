cmake_minimum_required(VERSION 3.3)

project(Strategy)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runStrategyTests
        strategy_test.cpp)

target_link_libraries(runStrategyTests gtest gtest_main)