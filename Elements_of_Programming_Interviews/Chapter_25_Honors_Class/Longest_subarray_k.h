#ifndef ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_K_H
#define ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_K_H
// 25.38 Find the longest subarray whose sum <= k

#include <algorithm>
#include <utility>
#include <vector>

using std::min;
using std::vector;

namespace long_sub {
// @include
    struct Subarray {
        int start, end;
    };

    Subarray find_longest_subarray_less_equal_k(const vector<int> &A, int k) {
        // Build the prefix sum according to A.
        vector<int> prefix_sum;
        partial_sum(A.cbegin(), A.cend(), back_inserter(prefix_sum));

        vector<int> min_prefix_sum(prefix_sum);
        for (int i = min_prefix_sum.size() - 2; i >= 0; --i) {
            min_prefix_sum[i] = min(min_prefix_sum[i], min_prefix_sum[i + 1]);
        }

        // initial solution from index [0, arr_idx]
        Subarray arr_idx = Subarray{
                0, static_cast<int>(distance(
                        min_prefix_sum.cbegin(),
                        upper_bound(min_prefix_sum.cbegin(), min_prefix_sum.cend(), k) -
                        1))
        };

        for (int i = 0; i < prefix_sum.size(); ++i) {
            // solution from [i+1, idx] : length: idx - i
            auto idx =
                    distance(min_prefix_sum.cbegin(),
                             upper_bound(min_prefix_sum.cbegin(), min_prefix_sum.cend(),
                                         k + prefix_sum[i])) -
                    1;
            if (idx - i > arr_idx.end - arr_idx.start + 1) {
                arr_idx = {i + 1, static_cast<int>(idx)};
            }
        }
        return arr_idx;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_LONGEST_SUBARRAY_K_H
