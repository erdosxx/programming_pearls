cmake_minimum_required(VERSION 3.3)

project(column_12_sampling)

add_definitions(-std=c++11)

#set(HEADER_FILES
#        sort.h
#        )

set(SOURCE_FILES
        sortedrand.cpp
        )

add_library(column_12_sampling STATIC ${SOURCE_FILES} ${HEADER_FILES})