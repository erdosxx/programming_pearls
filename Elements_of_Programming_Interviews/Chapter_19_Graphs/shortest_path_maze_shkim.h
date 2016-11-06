#ifndef ALGORITHM_ANALYSIS_SHORTEST_PATH_MAZE_SHKIM_H
#define ALGORITHM_ANALYSIS_SHORTEST_PATH_MAZE_SHKIM_H
// Variant problem for 19.1 from shkim.

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

namespace shkim {

    struct Pos {
        Pos(int r, int c, int d) : row(r), col(c), dist(d) {};
        int row;
        int col;
        int dist;
    };

    bool isSafe(int row, int col, int rows, int columns) {
        return (row >= 0 && row < rows) &&
               (col >= 0 && col < columns);
    }


    int findMinNumSteps(int **maze, int rows, int columns, int exitRow, int exitCol) {
        int row_move[] = {-1, 0, 0, 1};
        int col_move[] = {0, -1, 1, 0};

        vector <vector<bool>> visited;
        for (int i = 0; i < rows; ++i) {
            vector<bool> temp(columns, 0);
            visited.push_back(temp);
        }

        visited[0][0] = true;

        queue <Pos> q;
        Pos init(0, 0, 0);
        q.push(init);

        while (!q.empty()) {

            Pos curr = q.front();
            q.pop();

            if (curr.row == exitRow && curr.col == exitCol) {
                return curr.dist;
            }

            for (size_t i = 0; i < sizeof(row_move) / sizeof(int); ++i) {

                int new_row = curr.row + row_move[i];
                int new_col = curr.col + col_move[i];

                if (isSafe(new_row, new_col, rows, columns)) {
                    if (!maze[new_row][new_col] && !visited[new_row][new_col]) {

                        visited[new_row][new_col] = true;
                        Pos p(new_row, new_col, curr.dist + 1);
                        q.push(p);
                    }
                }
            }
        }

        return -1;
    }
}

#endif //ALGORITHM_ANALYSIS_SHORTEST_PATH_MAZE_SHKIM_H
