cmake_minimum_required(VERSION 3.3)

project(Template_Method)

add_definitions(-std=c++14)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTemplateMethodTests
        template_method_test.cpp)

target_link_libraries(runTemplateMethodTests gtest gtest_main)