#ifndef ALGORITHM_ANALYSIS_ROOK_ATTACK_H
#define ALGORITHM_ANALYSIS_ROOK_ATTACK_H
// 25.7 Identify positions attacked by rooks

#include <algorithm>
#include <vector>

using std::vector;

// @include
void RookAttack(vector<vector<int>>* A_ptr) {
    vector<vector<int>>& A = *A_ptr;
    size_t m = A.size();
    size_t n = A[0].size();

    bool has_first_row_zero = false;
    for (size_t j = 0; j < n; ++j) {
        if (!A[0][j]) {
            has_first_row_zero = true;
            break;
        }
    }

    bool has_first_column_zero = false;
    for (size_t i = 0; i < m; ++i) {
        if (!A[i][0]) {
            has_first_column_zero = true;
            break;
        }
    }

    for (size_t i = 1; i < m; ++i) {
        for (size_t j = 1; j < n; ++j) {
            if (!A[i][j]) {
                A[i][0] = A[0][j] = 0;
            }
        }
    }

    for (size_t i = 1; i < m; ++i) {
        if (!A[i][0]) {
            for (size_t j = 1; j < n; ++j) {
                A[i][j] = 0;
            }
        }
    }

    for (size_t j = 1; j < n; ++j) {
        if (!A[0][j]) {
            for (size_t i = 1; i < m; ++i) {
                A[i][j] = 0;
            }
        }
    }

    if (has_first_row_zero) {
        for (size_t j = 0; j < n; ++j) {
            A[0][j] = 0;
        }
    }
    if (has_first_column_zero) {
        for (size_t i = 0; i < m; ++i) {
            A[i][0] = 0;
        }
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_ROOK_ATTACK_H
