cmake_minimum_required(VERSION 3.3)

project(Ch6_Arrays C CXX)

#for supporting equal(first1, last1, first2, last2) c++14 is required.
add_definitions(-std=c++14)

set(HEADER_FILES
        Dutch_national_flag.h
        dutch_national_flag_slow_inplace.h
        dutch_national_flag_two_passes.h
        dutch_national_flag_bentley.h
        plus-one.h
        Bignumber_multiplication.h
        execute-shell.h
        jump-game.h
        remove-duplicates-from-sorted-array.h
        buy-and-sell-stock.h
        buy-and-sell-stock-twice.h
        prime-sieve-basic.h
        Prime_sieve.h
        Permutation_array1.h
        Permutation_array2.h
        Next_permutation.h
        Offline_sampling.h
        Reservoir_sampling.h
        compute_random_permutation.h
        Online_sampling.h
        nonuniform_random_number_generation.h
        sudoku_check.h
        Spiral_matrix_clockwise.h
        Spiral_matrix.h
        Matrix_rotation_constant.h
        Matrix_rotation_naive.h
        pascal-triangle-1.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch6_Arrays STATIC ${SOURCE_FILES} ${HEADER_FILES})