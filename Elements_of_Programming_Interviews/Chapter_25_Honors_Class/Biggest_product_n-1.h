#ifndef ALGORITHM_ANALYSIS_BIGGEST_PRODUCT_N_1_H
#define ALGORITHM_ANALYSIS_BIGGEST_PRODUCT_N_1_H

#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

using std::max;
using std::multiplies;
using std::numeric_limits;
using std::vector;

// @include
int FindBiggestNMinusOneProduct(const vector<int>& A) {
    // Builds forward product L, and backward product R.
    vector<int> L, R(A.size());
    partial_sum(A.cbegin(), A.cend(), back_inserter(L), multiplies<int>());
    partial_sum(A.crbegin(), A.crend(), R.rbegin(), multiplies<int>());

    // Finds the biggest product of (n - 1) numbers.
    int max_product = numeric_limits<int>::min();

    for (int i = 0; i < A.size(); ++i) {
        int forward = i > 0 ? L[i - 1] : 1;
        int backward = i + 1 < A.size() ? R[i + 1] : 1;
        max_product = max(max_product, forward * backward);
    }
    return max_product;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_BIGGEST_PRODUCT_N_1_H
