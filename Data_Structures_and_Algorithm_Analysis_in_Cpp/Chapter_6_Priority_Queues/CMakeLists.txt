cmake_minimum_required(VERSION 3.3)

project(Ch6_Priority_Queues C CXX)

add_definitions(-std=c++11)

set(HEADER_FILES
        LeftistHeap.h
        BinaryHeap.h
        BinomialQueue.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

#add_library(Ch6_Priority_Queues STATIC ${SOURCE_FILES} ${HEADER_FILES})