#ifndef ALGORITHM_ANALYSIS_SHORTEST_PATH_MAZE_JAYTHE1ST_H
#define ALGORITHM_ANALYSIS_SHORTEST_PATH_MAZE_JAYTHE1ST_H
// Variant problem for 19.1 from jaythe1st
// This solution is wrong, because of its low speed.

#include <iostream>
using namespace std;

namespace jaythe1st {
    const int VISIT = -1;
    const int UNVISIT = 0;

    const int min(int a, int b) { return a < b ? a : b; }

    bool canMove(int **maze, int rows, int columns, int r, int c) {
        if ((c < 0 || c >= columns) || (r < 0 || r >= rows))
            return false;
        return maze[r][c] == UNVISIT;
    }

    void moveto(int **maze, int rows, int columns, int exitRow, int exitCol,
                int r, int c, int &minSteps, int steps) {
        if (!canMove(maze, rows, columns, r, c)) return;

        if (minSteps <= steps)
            return; // pruning

        if (c == exitCol && r == exitRow) {
            minSteps = min(minSteps, steps);
            return;
        }

        maze[r][c] = VISIT;

        moveto(maze, rows, columns, exitRow, exitCol, r, c + 1, minSteps, steps + 1); // move right
        moveto(maze, rows, columns, exitRow, exitCol, r, c - 1, minSteps, steps + 1); // move left
        moveto(maze, rows, columns, exitRow, exitCol, r - 1, c, minSteps, steps + 1); // move up
        moveto(maze, rows, columns, exitRow, exitCol, r + 1, c, minSteps, steps + 1); // move down

        maze[r][c] = UNVISIT;
    }

    int findMinNumSteps(int **maze, int rows, int columns, int exitRow, int exitCol) {
        const int max = rows * columns;
        int minDist = max;
        moveto(maze, rows, columns, exitRow, exitCol, 0, 0, minDist, 0);

        return (minDist < max) ? minDist : -1;
    }
}

#endif //ALGORITHM_ANALYSIS_SHORTEST_PATH_MAZE_JAYTHE1ST_H
