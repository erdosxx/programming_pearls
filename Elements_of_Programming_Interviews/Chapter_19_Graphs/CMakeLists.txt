cmake_minimum_required(VERSION 3.3)

project(Ch19_Graphs C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        graphs_boot_camp.h
        team_reachability.h
        Search_maze.h
        shortest_path_maze.h
        shortest_path_maze_jaythe1st.h
        Painting_iterative.h
        surrounded-regions.h
        2-exists.h
        clone-graph.h
        Wiring_circuit_board.h
        Transform_string_to_other.h
        Team_photo_2.h
        Shortest_path_fewest_edges.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch19_Graphs STATIC ${SOURCE_FILES} ${HEADER_FILES})