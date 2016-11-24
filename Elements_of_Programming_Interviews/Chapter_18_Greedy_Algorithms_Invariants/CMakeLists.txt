cmake_minimum_required(VERSION 3.3)

project(Ch18_Greedy_Invariants C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        coin_change.h
        Task_assignment.h
        Minimum_waiting_time.h
        Points_covering_intervals.h
        Points_covering_intervals_alternative.h
        Points_covering_intervals_sorting.h
        2_sum.h
        3-sum.h
        Search_majority.h
        Gassing_up.h
        container-with-most-water.h
        Largest_rectangle_under_skyline.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch18_Greedy_Invariants STATIC ${SOURCE_FILES} ${HEADER_FILES})