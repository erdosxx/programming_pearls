cmake_minimum_required(VERSION 3.3)

project(column_11_sorting)

add_definitions(-std=c++11)

#set(HEADER_FILES
#        )

set(SOURCE_FILES
        sort.cpp
        )

add_library(column_11_sorting STATIC ${SOURCE_FILES} ${HEADER_FILES})