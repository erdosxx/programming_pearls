cmake_minimum_required(VERSION 3.3)

project(Observer)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runObserverTests
        observer_test.cpp)

target_link_libraries(runObserverTests gtest gtest_main)