cmake_minimum_required(VERSION 3.3)

project(Facade)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runFacadeTests
        facade_test.cpp)

target_link_libraries(runFacadeTests gtest gtest_main)