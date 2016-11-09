#ifndef ALGORITHM_ANALYSIS_LONGEST_INCREASING_SUBARRAY_H
#define ALGORITHM_ANALYSIS_LONGEST_INCREASING_SUBARRAY_H
// 25.5 Compute the longest contiguous increasing subarray

#include <algorithm>
#include <utility>
#include <vector>

using std::vector;

// @include
struct Subarray {
    int start = 0, end = 0;
};

Subarray FindLongestIncreasingSubarray(const vector<int> &A) {
    int max_length = 1;
    Subarray ans;
    int i = 0;

    while (i < A.size() - max_length) {
        // Backward check and skip if A[j - 1] >= A[j].
        bool is_skippable = false;

        for (int j = i + max_length; j > i; --j) {
            if (A[j - 1] >= A[j]) {
                i = j;
                is_skippable = true;
                break;
            }
        }

        // Forward check if it is not skippable.
        if (!is_skippable) {
            i += max_length;
            while (i < A.size() && A[i - 1] < A[i]) {
                ++i, ++max_length;
            }
            ans = {i - max_length, i - 1};
        }
    }
    return ans;
}
// @exclude


#endif //ALGORITHM_ANALYSIS_LONGEST_INCREASING_SUBARRAY_H
