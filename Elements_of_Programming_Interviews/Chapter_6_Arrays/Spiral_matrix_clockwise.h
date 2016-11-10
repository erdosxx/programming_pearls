#ifndef ALGORITHM_ANALYSIS_SPIRAL_MATRIX_CLOCKWISE_H
#define ALGORITHM_ANALYSIS_SPIRAL_MATRIX_CLOCKWISE_H
// 6.17 Compute the spiral ordering of a 2D array

#include <cmath>
#include <vector>

using std::vector;

namespace spiral_matrix_clockwise {
    void MatrixLayerInClockwise(const vector<vector<int>> &, int, vector<int> *);

// @include
    vector<int> MatrixInSpiralOrder(const vector<vector<int>> &square_matrix) {
        vector<int> spiral_ordering;
        for (int offset = 0; offset < ceil(0.5 * square_matrix.size()); ++offset) {
            MatrixLayerInClockwise(square_matrix, offset, &spiral_ordering);
        }
        return spiral_ordering;
    }

    void MatrixLayerInClockwise(const vector<vector<int>> &square_matrix,
                                int offset, vector<int> *spiral_ordering) {
        if (offset == square_matrix.size() - offset - 1) {
            // square_matrix has odd dimension, and we are at the center of
            // square_matrix.
            spiral_ordering->emplace_back(square_matrix[offset][offset]);
            return;
        }

        // -->
        for (int j = offset; j < square_matrix.size() - offset - 1; ++j) {
            spiral_ordering->emplace_back(square_matrix[offset][j]);
        }
        // |
        // v
        for (int i = offset; i < square_matrix.size() - offset - 1; ++i) {
            spiral_ordering->emplace_back(
                    square_matrix[i][square_matrix.size() - offset - 1]);
        }
        // <--
        for (int j = square_matrix.size() - offset - 1; j > offset; --j) {
            spiral_ordering->emplace_back(
                    square_matrix[square_matrix.size() - offset - 1][j]);
        }
        // ^
        // |
        for (int i = square_matrix.size() - offset - 1; i > offset; --i) {
            spiral_ordering->emplace_back(square_matrix[i][offset]);
        }
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_SPIRAL_MATRIX_CLOCKWISE_H
