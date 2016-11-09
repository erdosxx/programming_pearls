#ifndef ALGORITHM_ANALYSIS_MAXIMUM_SUBARRAY_IN_CIRCULAR_ARRAY_CONSTANT_SPACE_H
#define ALGORITHM_ANALYSIS_MAXIMUM_SUBARRAY_IN_CIRCULAR_ARRAY_CONSTANT_SPACE_H
// 25.31 Compute the maximum subarray sum in a circular array

#include <algorithm>
#include <vector>

using std::max;
using std::min;
using std::vector;

// See 17. Max-sum_subarray.h
namespace const_sp {

    int FindOptimumSubarrayUsingComp(const vector<int> &A,
                                     const int& (*comp)(const int &, const int &)) {
        int till = 0;
        int overall = 0;

        for (int a : A) {
            till = comp(a, a + till);
            overall = comp(overall, till);
        }

        return overall;
    }

// @include
    int MaxSubarraySumInCircular(const vector<int> &A) {
        // Finds the max in non-circular case and circular case.
        return max(FindOptimumSubarrayUsingComp(A, max),  // Non-circular case.
                   accumulate(A.cbegin(), A.cend(), 0) -
                   FindOptimumSubarrayUsingComp(A, min));  // Circular case.
    }

// @exclude
}

#endif //ALGORITHM_ANALYSIS_MAXIMUM_SUBARRAY_IN_CIRCULAR_ARRAY_CONSTANT_SPACE_H
