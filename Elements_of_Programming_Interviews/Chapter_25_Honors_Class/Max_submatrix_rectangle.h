#ifndef ALGORITHM_ANALYSIS_MAX_SUBMATRIX_RECTANGLE_H
#define ALGORITHM_ANALYSIS_MAX_SUBMATRIX_RECTANGLE_H

#include <algorithm>
#include <deque>
#include <limits>
#include <vector>

#include "Max_submatrix_rectangle_brute_force.h"

using std::deque;
using std::max;
using std::min;
using std::numeric_limits;
using std::vector;

// @include
struct MaxHW {
    int height, width;
};

int MaxRectangleSubmatrix(const vector<deque<bool>>& A) {
    // DP table stores (h, w) for each (i, j).
    vector<vector<MaxHW>> table(A.size(), vector<MaxHW>(A.front().size()));

    for (int i = A.size() - 1; i >= 0; --i) {
        for (int j = A[i].size() - 1; j >= 0; --j) {
            // Find the largest h such that (i, j) to (i + h - 1, j) are feasible.
            // Find the largest w such that (i, j) to (i, j + w - 1) are feasible.
            table[i][j] =
                    A[i][j] ? MaxHW{i + 1 < A.size() ? table[i + 1][j].height + 1 : 1,
                                    j + 1 < A[i].size() ? table[i][j + 1].width + 1 : 1}
                            : MaxHW{0, 0};
        }
    }

    int max_rect_area = 0;
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
            // Process (i, j) if it is feasible and is possible to update
            // max_rect_area.
            if (A[i][j] && table[i][j].width * table[i][j].height > max_rect_area) {
                int min_width = numeric_limits<int>::max();
                for (int a = 0; a < table[i][j].height; ++a) {
                    min_width = min(min_width, table[i + a][j].width);
                    max_rect_area = max(max_rect_area, min_width * (a + 1));
                }
            }
        }
    }
    return max_rect_area;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_MAX_SUBMATRIX_RECTANGLE_H
