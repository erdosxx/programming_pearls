cmake_minimum_required(VERSION 3.3)

project(Ch8_Disjoint_Sets C CXX)

add_definitions(-std=c++11)

set(HEADER_FILES
        DisjSets.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch8_Disjoint_Sets STATIC ${SOURCE_FILES} ${HEADER_FILES})