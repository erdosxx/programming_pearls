cmake_minimum_required(VERSION 3.3)

project(Chain_of_Responsibility)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runChainOfResponsibilityTests
        chain_of_responsibility_test.cpp)

target_link_libraries(runChainOfResponsibilityTests gtest gtest_main)