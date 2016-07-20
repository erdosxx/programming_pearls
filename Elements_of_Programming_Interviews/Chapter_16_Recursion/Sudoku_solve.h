#ifndef ALGORITHM_ANALYSIS_SUDOKU_SOLVE_H
#define ALGORITHM_ANALYSIS_SUDOKU_SOLVE_H

#include <algorithm>
#include <vector>

using std::vector;

bool SolvePartialSudoku(int, int, vector<vector<int>>*);
bool ValidToAddVal(const vector<vector<int>>&, int, int, int);

// @include
enum {kEmptyEntry = 0};

bool SolveSudoku(vector<vector<int>>* partial_assignment) {
    return SolvePartialSudoku(0, 0, partial_assignment);
}

// try from column 0 to column size()-1
bool SolvePartialSudoku(int row, int column,
                        vector<vector<int>>* partial_assignment) {
    if (row == partial_assignment->size()) {
        row = 0;  // set to the first row.
        if (++column == (*partial_assignment)[row].size()) {
            return true;  // Entire matrix has been filled without conflict.
        }
    }

    // Skips nonempty entries.
    if ((*partial_assignment)[row][column] != kEmptyEntry) {
        return SolvePartialSudoku(row + 1, column, partial_assignment);
    }

    for (int val = 1; val <= partial_assignment->size(); ++val) {
        // It's substantially quicker to check if entry val conflicts
        // with any of the constraints if we add it at (i,j) before
        // adding it, rather than adding it and then checking all constraints.
        // The reason is that we know we are starting with a valid configuration,
        // and the only entry which can cause a problem is entryval at (i,j).
        if (ValidToAddVal(*partial_assignment, row, column, val)) {
            (*partial_assignment)[row][column] = val;
            if (SolvePartialSudoku(row + 1, column, partial_assignment)) {
                return true;
            }
        }
    }

    (*partial_assignment)[row][column] = kEmptyEntry;  // Undo assignment.
    return false;
}

bool ValidToAddVal(const vector<vector<int>>& partial_assignment, int i,
                   int j, int val) {
    // Check row constraints.
    for (int k = 0; k < partial_assignment.size(); ++k) {
        if (val == partial_assignment[k][j]) {
            return false;
        }
    }

    // Check column constraints.
    for (int k = 0; k < partial_assignment.size(); ++k) {
        if (val == partial_assignment[i][k]) {
            return false;
        }
    }

    // Check region constraints.
    int region_size = sqrt(partial_assignment.size());
    int I = i / region_size, J = j / region_size;
    for (int a = 0; a < region_size; ++a) {
        for (int b = 0; b < region_size; ++b) {
            if (val ==
                partial_assignment[region_size * I + a][region_size * J + b]) {
                return false;
            }
        }
    }
    return true;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SUDOKU_SOLVE_H
