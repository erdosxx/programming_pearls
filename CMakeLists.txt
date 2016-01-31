cmake_minimum_required(VERSION 3.3)
project(programming_pearls)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(sort_run ${SOURCE_FILES})

include_directories(column_11_sorting)

add_subdirectory(column_11_sorting)
add_subdirectory(column_11_sorting_tests)

target_link_libraries(sort_run column_11_sorting)
