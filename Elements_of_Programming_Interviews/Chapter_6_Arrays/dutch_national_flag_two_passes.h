#ifndef ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_TWO_PASSES_H
#define ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_TWO_PASSES_H
// 6.1 The Dutch national flag problem

#include <algorithm>
#include <vector>
#include "Dutch_national_flag.h"

using std::swap;
using std::vector;
using DutchFlag::Color;

// @include
namespace DutchFlag_two {
    void DutchFlagPartition(const int& pivot_index, vector<Color> *A_ptr) {
        vector<Color> &A = *A_ptr;
        Color pivot = A[pivot_index];

        //  |    <    |   unknown     |
        //             |next_to_small
        // First pass: group elements smaller than pivot.
        int next_to_small = 0;
        for (int i = 0; i < A.size(); ++i) {
            if (A[i] < pivot) {
                swap(A[i], A[next_to_small++]);
            }
        }

        //  |  unknown   |     >     |
        //              | next_to_larger
        // Second pass: group elements larger than pivot.
        int next_to_larger = A.size() - 1;
        //for (int i = A.size() - 1; i >= 0 && A[i] >= pivot; --i) {
        for (int i = A.size() - 1; i >= next_to_small; --i) {
            if (A[i] > pivot) {
                swap(A[i], A[next_to_larger--]);
            }
        }
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_TWO_PASSES_H
