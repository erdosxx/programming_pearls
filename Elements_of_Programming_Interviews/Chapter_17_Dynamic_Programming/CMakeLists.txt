cmake_minimum_required(VERSION 3.3)

project(Ch17_DP C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        fibonacci.h
        Max-sum_subarray.h
        Score_combination.h
        Levenshtein_distance.h
        Number_ways.h
        Computing_binomial_coefficients.h
        String_in_matrix.h
        0-1_knapsack.h
        Word_breaking.h
        triangle.h
        Picking_up_coins.h
        number-steps.h
        Pretty_printing.h
        Longest_nondecreasing_subsequence_n2.h
        Longest_nondecreasing_subsequence_nlogn.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch17_DP STATIC ${SOURCE_FILES} ${HEADER_FILES})