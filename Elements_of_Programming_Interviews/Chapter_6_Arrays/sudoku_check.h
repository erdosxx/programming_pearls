#ifndef ALGORITHM_ANALYSIS_SUDOKU_CHECK_H
#define ALGORITHM_ANALYSIS_SUDOKU_CHECK_H
// 6.16 The Sudoku checker problem

#include <cassert>
#include <cmath>
#include <deque>
#include <vector>

using std::deque;
using std::vector;

// Return true if subarray partial_assignment[start_row : end_row -
// 1][start_col : end_col - 1] contains any duplicates in {1, 2, ...,
// partial_assignment.size()}; otherwise return false.
bool HasDuplicate(const vector<vector<int>>& partial_assignment,
                  int start_row, int end_row, int start_col, int end_col) {
    deque<bool> is_present(partial_assignment.size() + 1, false);

    for (int i = start_row; i < end_row; ++i) {
        for (int j = start_col; j < end_col; ++j) {
            if (partial_assignment[i][j] != 0 &&
                is_present[partial_assignment[i][j]]) {
                return true;
            }
            is_present[partial_assignment[i][j]] = true;
        }
    }
    return false;
}

// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
    // Check row constraints.
    for (int i = 0; i < partial_assignment.size(); ++i) {
        if (HasDuplicate(partial_assignment, i, i + 1, 0,
                         partial_assignment.size())) {
            return false;
        }
    }

    // Check column constraints.
    for (int j = 0; j < partial_assignment.size(); ++j) {
        if (HasDuplicate(partial_assignment, 0, partial_assignment.size(), j,
                         j + 1)) {
            return false;
        }
    }

    // Check region constraints.
    int region_size = sqrt(partial_assignment.size());
    for (int I = 0; I < region_size; ++I) {
        for (int J = 0; J < region_size; ++J) {
            if (HasDuplicate(partial_assignment, region_size * I,
                             region_size * (I + 1), region_size * J,
                             region_size * (J + 1))) {
                return false;
            }
        }
    }
    return true;
}

#endif //ALGORITHM_ANALYSIS_SUDOKU_CHECK_H
