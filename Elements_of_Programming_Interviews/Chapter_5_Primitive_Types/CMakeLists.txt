cmake_minimum_required(VERSION 3.3)

project(Ch5_Primitive_Types C CXX)

add_definitions(-std=c++11)

set(HEADER_FILES
        count_bits.h
        Parity1.h
        Parity2.h
        Parity3.h
        Parity4.h
        swapbits.h
        Reverse_bits.h
        Closest_int_same_bits.h
        MultiplyShiftAdd.h
        Division.h
        power-x-y.h
        reverse-integer.h
        palindrome-number.h
        Uniform_random_number_generation.h
        Intersect_rectangle.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch5_Primitive_Types STATIC ${SOURCE_FILES} ${HEADER_FILES})