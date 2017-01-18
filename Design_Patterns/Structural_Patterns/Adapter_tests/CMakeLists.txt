cmake_minimum_required(VERSION 3.3)

project(Adapter)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runAdapterTests
        adapter_test.cpp)

target_link_libraries(runAdapterTests gtest gtest_main)