cmake_minimum_required(VERSION 3.3)

project(Proxy)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runProxyTests
        proxy_test.cpp)

target_link_libraries(runProxyTests gtest gtest_main)