cmake_minimum_required(VERSION 3.3)

project(Ch5_Graph_Traversal)

add_definitions(-std=c++11)

set(HEADER_FILES
        graph_skeina.h
        List.h
        Vector.h
        dsexceptions.h
        bool.h
        graph.h
        item.h
        queue.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

#add_library(Ch5_Graph_Traversal STATIC ${SOURCE_FILES} ${HEADER_FILES})