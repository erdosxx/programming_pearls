#ifndef ALGORITHM_ANALYSIS_MATRIX_ROTATION_NAIVE_H
#define ALGORITHM_ANALYSIS_MATRIX_ROTATION_NAIVE_H

#include <algorithm>
#include <vector>

using std::cout;
using std::vector;

namespace matrix_rotation_naive {

    void PrintMatrix(const vector<vector<int>> &A) {
        for (int i = 0; i < A.size(); ++i) {
            // copy(A[i].begin(), A[i].end(), ostream_iterator<int>(cout, " "));
            for (int j = 0; j < A.size(); ++j) {
                cout << "A[" << i << "," << j << "] = " << A[i][j] << "  ";
            }
            cout << endl;
        }
    }

    bool CheckAnswer(const vector<vector<int>> &A) {
        int k = 1;
        for (int j = A.size() - 1; j >= 0; --j) {
            for (int i = 0; i < A.size(); ++i) {
                if (k++ != A[i][j])
                    return false;
            }
        }
        return true;
    }

// @include
    void RotateMatrix(vector<vector<int>> *square_matrix_ptr) {
        vector<vector<int>> &square_matrix = *square_matrix_ptr;
        const int matrix_size = square_matrix.size() - 1;

        for (int i = 0; i < (square_matrix.size() / 2); ++i) {
            for (int j = i; j < matrix_size - i; ++j) {
                // Perform a 4-way exchange.
                int temp1 = square_matrix[matrix_size - j][i];
                int temp2 = square_matrix[matrix_size - i][matrix_size - j];
                int temp3 = square_matrix[j][matrix_size - i];
                int temp4 = square_matrix[i][j];
                square_matrix[i][j] = temp1;
                square_matrix[matrix_size - j][i] = temp2;
                square_matrix[matrix_size - i][matrix_size - j] = temp3;
                square_matrix[j][matrix_size - i] = temp4;
            }
        }
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_MATRIX_ROTATION_NAIVE_H
