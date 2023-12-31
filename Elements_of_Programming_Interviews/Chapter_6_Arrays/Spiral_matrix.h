#ifndef ALGORITHM_ANALYSIS_SPIRAL_MATRIX_H
#define ALGORITHM_ANALYSIS_SPIRAL_MATRIX_H
// 6.17 Compute the spiral ordering of a 2D array

#include <array>
#include <vector>

using std::array;
using std::vector;

namespace spiral_matrix {
    enum {DONE = 0};
// @include
    vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
        const array<array<int, 2>, 4> kShift = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
        int dir = 0, x = 0, y = 0;
        vector<int> spiral_ordering;

        for (int i = 0; i < square_matrix.size() * square_matrix.size(); ++i) {
            spiral_ordering.emplace_back(square_matrix[x][y]);
            square_matrix[x][y] = DONE;

            int next_x = x + kShift[dir][0];
            int next_y = y + kShift[dir][1];

            if (next_x < 0 || next_x >= square_matrix.size() || next_y < 0 ||
                next_y >= square_matrix.size() ||
                square_matrix[next_x][next_y] == DONE) {
                dir = (dir + 1) % 4;
                next_x = x + kShift[dir][0];
                next_y = y + kShift[dir][1];
            }
            x = next_x;
            y = next_y;
        }
        return spiral_ordering;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_SPIRAL_MATRIX_H
