#ifndef ALGORITHM_ANALYSIS_N_QUEENS_H
#define ALGORITHM_ANALYSIS_N_QUEENS_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

void SolveNQueens_upto_row(int n, int row, const unique_ptr<vector<int>> &col_placements,
                           vector<vector<int>> *solutions);
bool IsValid(const vector<int>&);

// @include
vector<vector<int>> NQueens(int n) {
    vector<vector<int>> solutions;
    SolveNQueens_upto_row(n, 0, make_unique<vector<int>>(), &solutions);
    return solutions;
}

void SolveNQueens_upto_row(int n, int row,
                           const unique_ptr<vector<int>> &col_placements,
                           vector<vector<int>> *solutions) {
    if (row == n) {
        // All queens are legally placed.
        // add column placement to the solution set.
        solutions->emplace_back(*col_placements);
    } else {
        for (int col = 0; col < n; ++col) {
            // try to placement at col.
            col_placements->emplace_back(col);
            if (IsValid(*col_placements)) {
                SolveNQueens_upto_row(n, row + 1, col_placements, solutions);
            }
            col_placements->pop_back(); // rollback for next column trial.
        }
    }
}

// Test if a newly placed queen will conflict any earlier queens
// placed before.
bool IsValid(const vector<int>& col_placements) {
    int check_row_id = col_placements.size() - 1;
    for (int i = 0; i < check_row_id; ++i) {
        int diff = abs(col_placements[i] - col_placements[check_row_id]);
        // if same column or diagonal placement
        if (diff == 0 || diff == check_row_id - i) {
            // A column or diagonal constraint is violated.
            return false;
        }
    }
    return true;
}
// @exclude

vector<string> ToTextRepresentation(const vector<int>& col_placement) {
    vector<string> sol;
    for (int row : col_placement) {
        string line(col_placement.size(), '.');
        line[row] = 'Q';
        sol.emplace_back(line);
    }
    return sol;
}

#endif //ALGORITHM_ANALYSIS_N_QUEENS_H
