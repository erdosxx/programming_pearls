cmake_minimum_required(VERSION 3.3)

project(Factory_Method)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runFactoryMethodTests
        factory_method_test.cpp)

target_link_libraries(runFactoryMethodTests gtest gtest_main)