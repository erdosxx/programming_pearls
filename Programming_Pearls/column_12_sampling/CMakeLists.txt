cmake_minimum_required(VERSION 3.3)

project(column_12_sampling)

add_definitions(-std=c++11)

set(HEADER_FILES
        column12.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(column_12_sampling STATIC ${SOURCE_FILES} ${HEADER_FILES})