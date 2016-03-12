cmake_minimum_required(VERSION 3.3)

project(appendix)

add_definitions(-std=c++11)

#set(HEADER_FILES
#        sort_weiss.h
#        column1.h
#        UniformRandom.h
#        )

set(SOURCE_FILES
        spacemod.cpp timemod.cpp
        )

add_executable(runSpaceMode
        spacemod.cpp)


add_executable(runTimeMode
        timemod.cpp)

