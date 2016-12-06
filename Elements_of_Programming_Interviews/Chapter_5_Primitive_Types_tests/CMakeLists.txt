cmake_minimum_required(VERSION 3.3)

project(Ch5_Primitive_Types)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runPrimitiveTypesTests
        primitive_types_test.cpp)

target_link_libraries(runPrimitiveTypesTests gtest gtest_main)