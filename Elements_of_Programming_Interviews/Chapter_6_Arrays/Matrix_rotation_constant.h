#ifndef ALGORITHM_ANALYSIS_MATRIX_ROTATION_CONSTANT_H
#define ALGORITHM_ANALYSIS_MATRIX_ROTATION_CONSTANT_H

#include <vector>

using std::vector;

namespace matrix_rotation_constant {

    void RotateMatrix(vector<vector<int>> *A_ptr) {
        auto &A = *A_ptr;
        const int matrix_size = A.size() - 1;

        for (int i = 0; i < (A.size() / 2); ++i) {
            for (int j = i; j < matrix_size - i ; ++j) {
                int temp = A[i][j];
                A[i][j] = A[matrix_size - j][i];
                A[matrix_size - j][i] = A[matrix_size - i][matrix_size - j];
                A[matrix_size - i][matrix_size - j] = A[j][matrix_size - i];
                A[j][matrix_size - i] = temp;
            }
        }
    }

// @include
    class RotatedMatrix {
    public:
        explicit RotatedMatrix(vector<vector<int>> *square_matrix)
                : square_matrix_(*square_matrix) { }

        int ReadEntry(int i, int j) const {
            return square_matrix_[matrix_size - j][i];
        }

        void WriteEntry(int i, int j, int v) {
            square_matrix_[matrix_size - j][i] = v;
        }
    private:
        vector<vector<int>> &square_matrix_;
        const int matrix_size = square_matrix_.size() -1;
    };
// @exclude

    bool CheckAnswer(vector<vector<int>> A, const vector<vector<int>> &B) {
        RotatedMatrix rA(&A);
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < A.size(); ++j) {
                if(rA.ReadEntry(i, j) != B[i][j])
                    return false;
            }
        }
        return true;
    }
}

#endif //ALGORITHM_ANALYSIS_MATRIX_ROTATION_CONSTANT_H
