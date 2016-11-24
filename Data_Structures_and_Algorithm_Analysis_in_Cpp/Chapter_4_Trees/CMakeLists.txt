cmake_minimum_required(VERSION 3.3)

project(Ch4_Trees C CXX)

add_definitions(-std=c++11)

set(HEADER_FILES
        AvlTree.h
        ../include/dsexceptions.h
        BinarySearchTree.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch4_Trees STATIC ${SOURCE_FILES} ${HEADER_FILES})