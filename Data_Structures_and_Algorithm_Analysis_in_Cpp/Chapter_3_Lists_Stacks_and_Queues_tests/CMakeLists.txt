cmake_minimum_required(VERSION 3.3)

project(Ch3_Lists_Stacks_and_Queues)

add_definitions(-std=c++11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runList_VectorTests
        List_Vector_test.cpp)


target_link_libraries(runList_VectorTests gtest gtest_main)
