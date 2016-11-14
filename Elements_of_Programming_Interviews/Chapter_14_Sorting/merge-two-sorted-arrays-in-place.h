#ifndef ALGORITHM_ANALYSIS_MERGE_TWO_SORTED_ARRAYS_IN_PLACE_H
#define ALGORITHM_ANALYSIS_MERGE_TWO_SORTED_ARRAYS_IN_PLACE_H
// 14.2 Merge two sorted arrays

#include <algorithm>
#include <string>
#include <vector>

using std::vector;

// @include
void MergeTwoSortedArrays(int A[], int m, int B[], int n) {
    int a = m - 1;
    int b = n - 1;
    int write_idx = m + n - 1;

    while (a >= 0 && b >= 0) {
        A[write_idx--] = A[a] > B[b] ? A[a--] : B[b--];
    }
    while (b >= 0) {
        A[write_idx--] = B[b--];
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_MERGE_TWO_SORTED_ARRAYS_IN_PLACE_H
