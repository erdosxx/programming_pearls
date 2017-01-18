cmake_minimum_required(VERSION 3.3)

project(Command C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        command_sample_code.h
        basic.h
        command.h
        )

set(SOURCE_FILES
        ../../dummy.cpp
        )

add_library(Command STATIC ${SOURCE_FILES} ${HEADER_FILES})