cmake_minimum_required(VERSION 3.3)

project(Ch14_Sorting C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        Intersect_sorted_array1.h
        Intersect_sorted_array2.h
        Intersect_sorted_array3.h
        merge-two-sorted-arrays-in-place.h
        Eliminate_duplicate.h
        Rendering_calendar.h
        insert-interval.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch14_Sorting STATIC ${SOURCE_FILES} ${HEADER_FILES})