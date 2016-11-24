cmake_minimum_required(VERSION 3.3)

project(Ch11_Heaps C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        heaps_boot_camp.h
        Merge_sorted_arrays.h
        sort_k-increasing-decreasing_array.h
        Approximate_sort.h
        Closest_stars.h
        Online_median.h
        k-largest-elements-binary-heap.h
        Stack_queue_using_heap.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch11_Heaps STATIC ${SOURCE_FILES} ${HEADER_FILES})