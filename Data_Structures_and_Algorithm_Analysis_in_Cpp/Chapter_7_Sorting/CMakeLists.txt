cmake_minimum_required(VERSION 3.3)

project(Ch7_Sorting C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        UniformRandom.h
        Sort.h
        RadixSort.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch6_Sorting STATIC ${SOURCE_FILES} ${HEADER_FILES})