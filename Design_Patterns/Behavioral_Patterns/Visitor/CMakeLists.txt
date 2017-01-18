cmake_minimum_required(VERSION 3.3)

project(Visitor C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        )

set(SOURCE_FILES
        ../../dummy.cpp
        )

add_library(Visitor STATIC ${SOURCE_FILES} ${HEADER_FILES})