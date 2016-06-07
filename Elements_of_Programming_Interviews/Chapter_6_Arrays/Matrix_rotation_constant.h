#ifndef ALGORITHM_ANALYSIS_MATRIX_ROTATION_CONSTANT_H
#define ALGORITHM_ANALYSIS_MATRIX_ROTATION_CONSTANT_H

#include <vector>

using std::vector;

namespace matrix_rotation_constant {

    void RotateMatrix(vector<vector<int>> *A_ptr) {
        auto &A = *A_ptr;
        for (int i = 0; i < (A.size() / 2); ++i) {
            for (int j = i; j < A.size() - i - 1; ++j) {
                int temp = A[i][j];
                A[i][j] = A[A.size() - 1 - j][i];
                A[A.size() - 1 - j][i] = A[A.size() - 1 - i][A.size() - 1 - j];
                A[A.size() - 1 - i][A.size() - 1 - j] = A[j][A.size() - 1 - i];
                A[j][A.size() - 1 - i] = temp;
            }
        }
    }

// @include
    class RotatedMatrix {
    public:
        explicit RotatedMatrix(vector<vector<int>> *square_matrix)
                : square_matrix_(*square_matrix) { }

        int ReadEntry(int i, int j) const {
            return square_matrix_[square_matrix_.size() - 1 - j][i];
        }

        void WriteEntry(int i, int j, int v) {
            square_matrix_[square_matrix_.size() - 1 - j][i] = v;
        }

    private:
        vector<vector<int>> &square_matrix_;
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
