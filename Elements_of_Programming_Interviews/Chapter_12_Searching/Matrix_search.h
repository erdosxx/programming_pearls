#ifndef ALGORITHM_ANALYSIS_MATRIX_SEARCH_H
#define ALGORITHM_ANALYSIS_MATRIX_SEARCH_H
// 12.6 Search in a 2D sorted array

#include <vector>

using std::vector;

bool MatrixSearch(const vector<vector<int>>& A, int x) {
    int row = 0, col = A[0].size() - 1;  // Start from the top-right corner.
    // Keeps searching while there are unclassified rows and columns.
    while (row < A.size() && col >= 0) {
        if (A[row][col] == x) {
            return true;
        } else if (A[row][col] < x) {
            ++row;  // Eliminate this row.
        } else {  // A[row][col] > x.
            --col;  // Eliminate this column.
        }
    }
    return false;
}

#endif //ALGORITHM_ANALYSIS_MATRIX_SEARCH_H
