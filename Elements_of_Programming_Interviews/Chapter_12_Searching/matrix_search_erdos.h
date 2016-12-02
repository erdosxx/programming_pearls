#ifndef ALGORITHM_ANALYSIS_MATRIX_SEARCH_ERDOS_H
#define ALGORITHM_ANALYSIS_MATRIX_SEARCH_ERDOS_H
// 12.6 Search in a 2D sorted array

// Ref: http://articles.leetcode.com/searching-2d-sorted-matrix-part-ii
// Above page contains other approaches.

#include <vector>

using std::vector;

// Search largest indexed value which is less or equal to k.
// Ex) {-1, 2, 4, 4, 6}  k= 5,  ans = 3
//                |
// Ex) {-1, 2, 5, 5, 6}  k= 5,  ans = 3
int Search_latest_less_equal_k(const vector<int>& A, const int& start, const int& end, const int& k) {
    int low = start;
    int high = end;
    int middle;
    int result = -1;

    while (low <= high) {
        middle = low + (high - low)/2;

        if (A[middle] > k) {
            high = middle -1;
        } else if (A[middle] <= k) {
            result = middle;
            low = middle +1;
        }
    }
    return result;
}

int Search_row_latest_less_equal_k_2D(const vector<vector<int>>& Matrix,
                                      const int& low_idx, const int& start, const int& end, const int& k) {
    const vector<int>& target_row = Matrix[low_idx];

    return Search_latest_less_equal_k(target_row, start, end, k);
}

int Search_col_latest_less_equal_k_2D(const vector<vector<int>>& Matrix,
                                      const int& col_idx, const int& start, const int& end, const int& k) {
    int low = start;
    int high = end;
    int middle;
    int result = -1;

    while (low <= high) {
        middle = low + (high - low)/2;

        if (Matrix[middle][col_idx] > k) {
            high = middle -1;
        } else if (Matrix[middle][col_idx] <= k) {
            result = middle;
            low = middle +1;
        }
    }
    return result;
}

bool MatrixSearch_erdos(const vector<vector<int>>& A, const int& x) {
    const int row_size = A.size();
    const int col_size = A[0].size();
    bool result = false;

    int curr_col = col_size -1;
    int curr_row = 0;

    while (0 <= curr_col && curr_col < col_size &&
            0 <= curr_row && curr_row < row_size) {
        curr_col = Search_row_latest_less_equal_k_2D(A, curr_row, 0, curr_col, x);

        if (curr_col == -1) {
            return false;
        } else if (A[curr_row][curr_col] == x) {
            return true;
        }

        curr_row = Search_col_latest_less_equal_k_2D(A, curr_col, curr_row, row_size -1, x);

        if (A[curr_row][curr_col] == x) {
            return true;
        } else if (curr_row == row_size -1) {
            return false;
        }

        curr_row++;
        curr_col--;
    }

    return result;
}

#endif //ALGORITHM_ANALYSIS_MATRIX_SEARCH_ERDOS_H
