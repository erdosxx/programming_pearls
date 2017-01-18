cmake_minimum_required(VERSION 3.3)

project(Singleton)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runSingletonTests
        singleton_test.cpp)

target_link_libraries(runSingletonTests gtest gtest_main)