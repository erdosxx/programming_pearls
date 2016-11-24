cmake_minimum_required(VERSION 3.3)

project(column_1_cracking_the_oyster C CXX)

add_definitions(-std=c++11)

set(HEADER_FILES
        sort_weiss.h
        column1.h
        UniformRandom.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(column_1_cracking_the_oyster STATIC ${SOURCE_FILES} ${HEADER_FILES})
