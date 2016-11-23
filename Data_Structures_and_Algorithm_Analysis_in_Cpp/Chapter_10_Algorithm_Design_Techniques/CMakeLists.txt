cmake_minimum_required(VERSION 3.3)

project(Ch10_Algorithm_Design C CXX)

add_definitions(-std=c++11)

set(HEADER_FILES
        matrix.h
        optMatrix.h
        all_pairs_shortest_path.h
        Random.h
        DSL.h
        primality.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

#add_library(Ch10_Algorithm_Design STATIC ${SOURCE_FILES} ${HEADER_FILES})