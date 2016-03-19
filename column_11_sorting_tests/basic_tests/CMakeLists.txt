include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicSortTests
#        basic_check.cpp
        sort_check.cpp)

target_link_libraries(runBasicSortTests gtest gtest_main)
target_link_libraries(runBasicSortTests column_11_sorting)