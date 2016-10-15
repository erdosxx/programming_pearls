#ifndef ALGORITHM_ANALYSIS_MAX_SUBMATRIX_SQUARE_H
#define ALGORITHM_ANALYSIS_MAX_SUBMATRIX_SQUARE_H

#include <algorithm>
#include <deque>
#include <vector>

using std::deque;
using std::max;
using std::min;
using std::vector;

namespace square {
// @include
    struct MaxHW {
        int height, width;
    };

    int MaxSquareSubmatrix(const vector<deque<bool>> &A) {
        // DP table stores (h, w) for each (i, j).
        vector<vector<MaxHW>> table(A.size(), vector<MaxHW>(A.front().size()));

        for (int row = A.size() - 1; row >= 0; --row) {
            for (int column = A[row].size() - 1; column >= 0; --column) {
                // Finds the largest h such that (i, j) to (i + h - 1, j) are feasible.
                // Finds the largest w such that (i, j) to (i, j + w - 1) are feasible.
                table[row][column] =
                        A[row][column] ? MaxHW{row + 1 < A.size() ? table[row + 1][column].height + 1 : 1,
                                        column + 1 < A[row].size() ? table[row][column + 1].width + 1 : 1}
                                : MaxHW{0, 0};
            }
        }

        // A table stores the length of the largest square for each (i, j).
        vector<vector<int>> s(A.size(), vector<int>(A.front().size(), 0));
        int max_square_area = 0;
        for (int row = A.size() - 1; row >= 0; --row) {
            for (int column = A[row].size() - 1; column >= 0; --column) {
                int side = min(table[row][column].height, table[row][column].width);

                if (A[row][column]) {
                    // Gets the length of largest square with bottom-left corner (i, j).
                    if (row + 1 < A.size() && column + 1 < A[row + 1].size()) {
                        side = min(s[row + 1][column + 1] + 1, side);
                    }
                    s[row][column] = side;
                    max_square_area = max(max_square_area, side * side);
                }
            }
        }
        return max_square_area;
    }
// @exclude
}


#endif //ALGORITHM_ANALYSIS_MAX_SUBMATRIX_SQUARE_H
