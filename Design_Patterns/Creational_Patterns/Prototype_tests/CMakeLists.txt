cmake_minimum_required(VERSION 3.3)

project(Prototype)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runPrototypeTests
        prototype_test.cpp)

target_link_libraries(runPrototypeTests gtest gtest_main)