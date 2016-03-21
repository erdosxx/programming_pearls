cmake_minimum_required(VERSION 3.3)
project(programming_pearls C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        column_1_cracking_the_oyster
        column_2_algorithms
        column_5_a_small_matter_of_programming
        column_8_algorithm_design_techniques
        column_9_code_tuning
        column_11_sorting
        column_12_sampling
        column_14_heaps
        )

add_subdirectory(lib/googletest)
add_subdirectory(column_1_cracking_the_oyster)
add_subdirectory(column_1_cracking_the_oyster_tests)
add_subdirectory(column_2_algorithms)
add_subdirectory(column_2_algorithms_tests)
add_subdirectory(column_5_a_small_matter_of_programming)
add_subdirectory(column_5_a_small_matter_of_programming_tests)
add_subdirectory(column_8_algorithm_design_techniques)
add_subdirectory(column_8_algorithm_design_techniques_tests)
add_subdirectory(column_9_code_tuning)
add_subdirectory(column_9_code_tuning_tests)
add_subdirectory(column_11_sorting)
add_subdirectory(column_11_sorting_tests)
add_subdirectory(column_12_sampling)
add_subdirectory(column_14_heaps)
add_subdirectory(column_14_heaps_tests)
add_subdirectory(appendix)

target_link_libraries(column_1_cracking_the_oyster)
target_link_libraries(column_2_algorithms)
target_link_libraries(column_11_sorting)
target_link_libraries(column_14_heaps)
