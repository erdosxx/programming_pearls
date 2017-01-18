cmake_minimum_required(VERSION 3.3)

project(Bridge)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBridgeTests
        bridge_test.cpp)

target_link_libraries(runBridgeTests gtest gtest_main)