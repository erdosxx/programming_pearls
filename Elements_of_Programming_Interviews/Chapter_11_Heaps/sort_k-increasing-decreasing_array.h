#ifndef ALGORITHM_ANALYSIS_SORT_K_INCREASING_DECREASING_ARRAY_H
#define ALGORITHM_ANALYSIS_SORT_K_INCREASING_DECREASING_ARRAY_H

#include <vector>

#include "Merge_sorted_arrays.h"

using std::vector;

// @include
vector<int> SortKIncreasingDecreasingArray(const vector<int>& A) {
    // Decomposes A into a set of sorted arrays.
    vector<vector<int>> sorted_subarrays;
    using SubarrayType = enum { INCREASING, DECREASING };

    SubarrayType subarray_type = INCREASING;
    int start_idx = 0;

    for (int i = 1; i <= A.size(); ++i) {
        if (i == A.size() ||  // A is ended. Adds the last subarray.
            (A[i - 1] < A[i] && subarray_type == DECREASING) ||
            (A[i - 1] >= A[i] && subarray_type == INCREASING)) {
            if (subarray_type == INCREASING) {
                // use vector constructor as following signature
                // template <class InputIterator>
                // vector (InputIterator first, InputIterator last,
                // const allocator_type& alloc = allocator_type());
                sorted_subarrays.emplace_back(A.cbegin() + start_idx, A.cbegin() + i);
            } else {
                // crbegin: Return const_reverse_iterator to reverse beginning
                sorted_subarrays.emplace_back(A.crbegin() + A.size() - i,
                                              A.crbegin() + A.size() - start_idx);
            }
            start_idx = i;
            subarray_type = (subarray_type == INCREASING ? DECREASING : INCREASING);
        }
    }

    return MergeSortedArrays(sorted_subarrays);
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SORT_K_INCREASING_DECREASING_ARRAY_H
