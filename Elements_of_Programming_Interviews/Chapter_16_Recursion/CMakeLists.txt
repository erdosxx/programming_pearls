cmake_minimum_required(VERSION 3.3)

project(Ch16_Recursion C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        tower_hanoi.h
        n-queens.h
        permutations.h
        permutations-alternative.h
        Power_set.h
        Power_set_alternative.h
        combinations.h
        generate-parentheses.h
        palindrome-partitioning.h
        unique-binary-trees-all.h
        Sudoku_solve.h
        gray-code.h
        gray-code-backtrack.h
        Tree_diameter.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch16_Recursion STATIC ${SOURCE_FILES} ${HEADER_FILES})