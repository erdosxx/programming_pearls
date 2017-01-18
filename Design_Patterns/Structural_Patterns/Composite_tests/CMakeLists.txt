cmake_minimum_required(VERSION 3.3)

project(Composite)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runCompositeTests
        composite_test.cpp)

target_link_libraries(runCompositeTests gtest gtest_main)