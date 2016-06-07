cmake_minimum_required(VERSION 3.3)
project(Data_Structures_and_Algorithm_Analysis_in_Cpp C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        include
        Chapter_3_Lists_Stacks_and_Queues
        Chapter_4_Trees
        Chapter_6_Priority_Queues
        Chapter_8_Disjoint_Sets
        Chapter_9_Graph_Algorithms
        Chapter_10_Algorithm_Design_Techniques
        Chapter_12_Advanced_Data_Structures_and_Implementation
        )

add_subdirectory(Chapter_3_Lists_Stacks_and_Queues)
add_subdirectory(Chapter_3_Lists_Stacks_and_Queues_tests)
add_subdirectory(Chapter_4_Trees)
add_subdirectory(Chapter_4_Trees_tests)
add_subdirectory(Chapter_6_Priority_Queues)
add_subdirectory(Chapter_6_Priority_Queues_tests)
add_subdirectory(Chapter_8_Disjoint_Sets)
add_subdirectory(Chapter_8_Disjoint_Sets_tests)
add_subdirectory(Chapter_9_Graph_Algorithms)
add_subdirectory(Chapter_9_Graph_Algorithms_tests)
add_subdirectory(Chapter_10_Algorithm_Design_Techniques)
add_subdirectory(Chapter_10_Algorithm_Design_Techniques_tests)
add_subdirectory(Chapter_12_Advanced_Data_Structures_and_Implementation)
add_subdirectory(Chapter_12_Advanced_Data_Structures_and_Implementation_tests)