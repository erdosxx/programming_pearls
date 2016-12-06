cmake_minimum_required(VERSION 3.3)
project(Elements_of_Programming_Interviews C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(
        Chapter_1_Getting_Ready
        Chapter_5_Primitive_Types
        Chapter_6_Arrays
        Chapter_7_Strings
        Chapter_8_Linked_Lists
        Chapter_9_Stacks_and_Queues
        Chapter_10_Binary_Trees
        Chapter_11_Heaps
        Chapter_12_Searching
        Chapter_13_Hash_Tables
        Chapter_14_Sorting
        Chapter_15_Binary_Search_Trees
        Chapter_16_Recursion
        Chapter_17_Dynamic_Programming
        Chapter_18_Greedy_Algorithms_Invariants
        Chapter_19_Graphs
        Chapter_20_Parallel_Computing
        Chapter_25_Honors_Class
        )

add_subdirectory(Chapter_1_Getting_Ready)
add_subdirectory(Chapter_1_Getting_Ready_tests)
add_subdirectory(Chapter_5_Primitive_Types)
add_subdirectory(Chapter_5_Primitive_Types_tests)
add_subdirectory(Chapter_6_Arrays)
add_subdirectory(Chapter_6_Arrays_tests)
add_subdirectory(Chapter_7_Strings)
add_subdirectory(Chapter_7_Strings_tests)
add_subdirectory(Chapter_8_Linked_Lists)
add_subdirectory(Chapter_8_Linked_Lists_tests)
add_subdirectory(Chapter_9_Stacks_and_Queues)
add_subdirectory(Chapter_9_Stacks_and_Queues_tests)
add_subdirectory(Chapter_10_Binary_Trees)
add_subdirectory(Chapter_10_Binary_Trees_tests)
add_subdirectory(Chapter_11_Heaps)
add_subdirectory(Chapter_11_Heaps_tests)
add_subdirectory(Chapter_12_Searching)
add_subdirectory(Chapter_12_Searching_tests)
add_subdirectory(Chapter_13_Hash_Tables)
add_subdirectory(Chapter_13_Hash_Tables_tests)
add_subdirectory(Chapter_14_Sorting)
add_subdirectory(Chapter_14_Sorting_tests)
add_subdirectory(Chapter_15_Binary_Search_Trees)
add_subdirectory(Chapter_15_Binary_Search_Trees_tests)
add_subdirectory(Chapter_16_Recursion)
add_subdirectory(Chapter_16_Recursion_tests)
add_subdirectory(Chapter_17_Dynamic_Programming)
add_subdirectory(Chapter_17_Dynamic_Programming_tests)
add_subdirectory(Chapter_18_Greedy_Algorithms_Invariants)
add_subdirectory(Chapter_18_Greedy_Algorithms_Invariants_tests)
add_subdirectory(Chapter_19_Graphs)
add_subdirectory(Chapter_19_Graphs_tests)
add_subdirectory(Chapter_20_Parallel_Computing)
add_subdirectory(Chapter_20_Parallel_Computing_tests)
add_subdirectory(Chapter_25_Honors_Class)
add_subdirectory(Chapter_25_Honors_Class_tests)
