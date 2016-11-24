cmake_minimum_required(VERSION 3.3)

project(Ch3_Lists_Stacks_and_Queues C CXX)

add_definitions(-std=c++11)

set(HEADER_FILES
        List.h
        Vector.h
        Queue.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch3_Lists_Stacks_and_Queues STATIC ${SOURCE_FILES} ${HEADER_FILES})