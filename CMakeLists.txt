cmake_minimum_required(VERSION 3.3)
project(programming_pearls)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(column_11_sorting)

add_subdirectory(lib/googletest)
add_subdirectory(column_1_cracking_the_oyster)
add_subdirectory(column_1_cracking_the_oyster_tests)
add_subdirectory(column_2_algorithms)

add_subdirectory(column_11_sorting)
add_subdirectory(column_11_sorting_tests)
add_subdirectory(column_12_sampling)

target_link_libraries(column_11_sorting)
