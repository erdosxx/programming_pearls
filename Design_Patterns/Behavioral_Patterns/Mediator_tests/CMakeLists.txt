cmake_minimum_required(VERSION 3.3)

project(Mediator)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runMediatorTests
        mediator_test.cpp)

target_link_libraries(runMediatorTests gtest gtest_main)