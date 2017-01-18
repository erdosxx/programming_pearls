cmake_minimum_required(VERSION 3.3)

project(Abstract_Factory)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runAbstractFactoryTests
        abstract_factory_test.cpp)

target_link_libraries(runAbstractFactoryTests gtest gtest_main)