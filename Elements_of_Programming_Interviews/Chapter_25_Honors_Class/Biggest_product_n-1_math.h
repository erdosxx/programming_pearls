#ifndef ALGORITHM_ANALYSIS_BIGGEST_PRODUCT_N_1_MATH_H
#define ALGORITHM_ANALYSIS_BIGGEST_PRODUCT_N_1_MATH_H

#include <vector>

using std::vector;

// @include
namespace alt_math {
    int FindBiggestNMinusOneProduct(const vector<int> &A) {
        int least_nonnegative_idx = -1;
        int number_of_negatives = 0, greatest_negative_idx = -1,
                least_negative_idx = -1;

        // Identify the least negative, greatest negative, and least nonnegative
        // entries.
        for (int i = 0; i < A.size(); ++i) {
            if (A[i] < 0) {
                ++number_of_negatives;

                if (least_negative_idx == -1 || A[least_negative_idx] < A[i]) {
                    least_negative_idx = i;
                }

                if (greatest_negative_idx == -1 || A[i] < A[greatest_negative_idx]) {
                    greatest_negative_idx = i;
                }
            } else {  // A[i] >= 0.
                if (least_nonnegative_idx == -1 || A[i] < A[least_nonnegative_idx]) {
                    least_nonnegative_idx = i;
                }
            }
        }

        int product = 1;
        int idx_to_skip =
                number_of_negatives % 2
                ? least_negative_idx
                // Check if there are any nonnegative entry.
                : (least_nonnegative_idx != -1 ? least_nonnegative_idx
                                               : greatest_negative_idx);
        for (int i = 0; i < A.size(); ++i) {
            if (i != idx_to_skip) {
                product *= A[i];
            }
        }
        return product;
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_BIGGEST_PRODUCT_N_1_MATH_H
