cmake_minimum_required(VERSION 3.3)

project(Ch15_Friends_Exceptions_and_More)

add_definitions(-std=c++17)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(HEADER_FILES
        exc_mean.h
        sales.h
        )

set(SOURCE_FILES
        error5.cpp
        sales.cpp
        use_sales.cpp
        )

add_library(Ch15_Friends_Exceptions_and_More STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(runError5 error5.cpp)

add_executable(runUseSales use_sales.cpp sales.cpp)

target_link_libraries(runError5 gtest gmock gtest_main)
target_link_libraries(runUseSales gtest gmock gtest_main)
