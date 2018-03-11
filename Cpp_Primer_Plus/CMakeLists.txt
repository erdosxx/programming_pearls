cmake_minimum_required(VERSION 3.3)
project(Cpp_Primer_Plus C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(
        Chapter15_Friends_Exceptions_and_More
)

add_subdirectory(Chapter15_Friends_Exceptions_and_More)
