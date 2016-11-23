cmake_minimum_required(VERSION 3.3)

project(Ch20_Parallel_Computing C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        s1.h
        s2.h
        two_thread_increment.h
        odd_even.h
        simple_web_server.h
        thread_per_task_webserver.h
        task_execution_web_server.h
        lock_ordering_bug.h
        lock_ordering_works.h
        collatz.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

#add_library(Ch20_Parallel_Computing STATIC ${SOURCE_FILES} ${HEADER_FILES})