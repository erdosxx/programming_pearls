#ifndef ALGORITHM_ANALYSIS_MAX_SUBMATRIX_RECTANGLE_IMPROVED_H
#define ALGORITHM_ANALYSIS_MAX_SUBMATRIX_RECTANGLE_IMPROVED_H

#include <algorithm>
#include <deque>
#include <vector>

#include "Largest_rectangle_under_skyline.h"
#include "Max_submatrix_rectangle_brute_force.h"

using std::deque;
using std::max;
using std::vector;

namespace impl {
// @include
    int MaxRectangleSubmatrix(const vector<deque<bool>> &A) {
        vector<int> table(A.front().size(), 0);
        int max_rect_area = 0;
        // Find the maximum among all instances of the largest rectangle.
        for (int row = 0; row < A.size(); ++row) {
            for (int column = 0; column < A[row].size(); ++column) {
                table[column] = A[row][column] ? table[column] + 1 : 0;
            }
            max_rect_area = max(max_rect_area, CalculateLargestRectangle(table));
        }
        return max_rect_area;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_MAX_SUBMATRIX_RECTANGLE_IMPROVED_H
