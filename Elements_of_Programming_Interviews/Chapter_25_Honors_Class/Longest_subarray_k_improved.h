#ifndef ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_K_IMPROVED_H
#define ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_K_IMPROVED_H

#include <algorithm>
#include <utility>
#include <vector>

using std::min;
using std::vector;

// @include
int FindLongestSubarrayLessEqualK(const vector<int> &A, int k) {
    // Builds the prefix sum according to A.
    vector<int> prefix_sum;
    partial_sum(A.cbegin(), A.cend(), back_inserter(prefix_sum));

    // Early returns if the sum of A is smaller than or equal to k.
    if (prefix_sum.back() <= k) {
        return A.size();
    }

    // Builds min_prefix_sum.
    vector<int> min_prefix_sum(A.size());
    min_prefix_sum.back() = prefix_sum.back();

    // min_prefix_sum is monotonic increasing sequence.
    for (int i = min_prefix_sum.size() - 2; i >= 0; --i) {
        min_prefix_sum[i] = min(prefix_sum[i], min_prefix_sum[i + 1]);
    }

    int a = 0, b = 0, max_length = 0;
    while (a < A.size() && b < A.size()) {
        // solution from index [a, b]
        int min_curr_sum =
                a > 0 ? min_prefix_sum[b] - prefix_sum[a - 1] : min_prefix_sum[b];
        if (min_curr_sum <= k) {
            int curr_length = b - a + 1;
            if (curr_length > max_length) {
                max_length = curr_length;
            }
            ++b;
        } else {  // min_curr_sum > k.
            ++a;
        }
    }
    return max_length;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_K_IMPROVED_H
