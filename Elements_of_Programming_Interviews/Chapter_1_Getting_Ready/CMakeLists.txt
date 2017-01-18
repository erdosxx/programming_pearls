cmake_minimum_required(VERSION 3.3)

project(Ch1_Getting_Ready C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        object_closure.h
        encapsulating_arguments.h
        booking_com_interview.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch1_Getting_Ready STATIC ${SOURCE_FILES} ${HEADER_FILES})