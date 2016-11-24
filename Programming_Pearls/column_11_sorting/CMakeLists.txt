cmake_minimum_required(VERSION 3.3)

project(column_11_sorting)

add_definitions(-std=c++11)

set(HEADER_FILES
        sort.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(column_11_sorting STATIC ${SOURCE_FILES} ${HEADER_FILES})