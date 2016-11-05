#ifndef ALGORITHM_ANALYSIS_SHORTEST_PATH_MAZE_H
#define ALGORITHM_ANALYSIS_SHORTEST_PATH_MAZE_H

#include <vector>
#include <queue>
#include <array>
#include <stdexcept>

using std::queue;
using std::vector;
using std::array;
using std::invalid_argument;

enum {WALL= 1, PATH= 0, NEW_WALL=-100, NEW_PATH= -10, UNREACHABLE=-1};

struct position {
    int row;
    int col;

    bool operator==(const position& that) const {
        return row == that.row && col == that.col;
    }
};

void initalize_maze(int **maze, const int &rows, const int &columns);
void reset_maze(int ** maze, const int & rows, const int &columns);
bool isValidPath(int** maze, const position& pos, const int& row_limit, const int& col_limit);
vector<position> get_adjacent_nodes(int **maze, const position& pos, const int& rows, const int& columns);

int findMinNumSteps(int **maze, const int& rows, const int& columns, const int& exitRow, const int& exitCol) {
    position start = {0,0};
    position exit = {exitRow, exitCol};

    if (start == exit) {
        return 0;
    }

    // use maze data for updating distance (in-place)
    initalize_maze(maze, rows, columns);

    maze[start.row][start.col] = 0; // distance for start

    queue<position> node_pos_que;

    node_pos_que.push(start);

    int distance = UNREACHABLE;

    while (!node_pos_que.empty()) {
        position node = node_pos_que.front();
        node_pos_que.pop();

        for (const position& adj_node : get_adjacent_nodes(maze, node, rows, columns)) {
            if(maze[adj_node.row][adj_node.col] == NEW_PATH) {
                // update distance.
                maze[adj_node.row][adj_node.col] = maze[node.row][node.col] + 1;
                node_pos_que.push(adj_node);

                if (adj_node.row == exitRow && adj_node.col == exitCol) { // if reach to Exit
                    distance = maze[exitRow][exitCol];

                    // resetting is optional for ease testing.
                    reset_maze(maze,rows,columns);

                    return distance;
                }
            }
        }
    }

    // resetting is optional for ease testing.
    reset_maze(maze,rows,columns);

    return distance;
}

// change maze for calculating distance
void initalize_maze(int **maze, const int &rows, const int &columns) {// change data for in-place solution
    for (int row=0; row < rows; ++row) {
        for (int col=0; col < columns ; ++col) {
            if (maze[row][col] == WALL) {
                maze[row][col] = NEW_WALL;
            } else { // PATH
                maze[row][col] = NEW_PATH;
            }
        }
    }
}

// restore to orginal maze
void reset_maze(int ** maze, const int & rows, const int &columns) {
    for (int row=0; row < rows; ++row) {
        for (int col=0; col < columns ; ++col) {
            if (maze[row][col] == NEW_WALL) {
                maze[row][col] = WALL;
            } else { // PATH
                maze[row][col] = PATH;
            }
        }
    }
}

bool isValidPath(int** maze, const position& pos, const int& row_limit, const int& col_limit) {
    if (pos.row < 0 || pos.row >= row_limit || pos.col < 0 || pos.col >= col_limit) {
        return false;
    }

    return maze[pos.row][pos.col] == NEW_WALL ? false : true;
}

vector<position> get_adjacent_nodes(int **maze, const position& pos, const int& rows, const int& columns) {
    vector<position> result;

    const array<array<int, 2>, 4> shifts {{{-1,0}, {0,1}, {1,0}, {0,-1}}};

    if(maze[pos.row][pos.col] == NEW_WALL) {
        throw invalid_argument("Search position is a wall!");
    }

    for (const array<int,2>& shift : shifts) {
        position adjacent = {pos.row + shift[0], pos.col + shift[1]};

        if(isValidPath(maze, adjacent, rows, columns))
            result.push_back(adjacent);
    }

    return result;
};

#endif //ALGORITHM_ANALYSIS_SHORTEST_PATH_MAZE_H
