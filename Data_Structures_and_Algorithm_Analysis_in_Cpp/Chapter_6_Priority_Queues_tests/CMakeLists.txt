cmake_minimum_required(VERSION 3.3)

project(Ch6_Priority_Queues)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runPriorityQueuesTests
        priority_queues_test.cpp)


target_link_libraries(runPriorityQueuesTests gtest gtest_main)