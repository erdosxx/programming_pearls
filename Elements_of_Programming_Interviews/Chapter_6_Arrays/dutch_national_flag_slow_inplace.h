#ifndef ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_SLOW_INPLACE_H
#define ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_SLOW_INPLACE_H
// 6.1 The Dutch national flag problem

#include <algorithm>
#include <vector>
#include "Dutch_national_flag.h"

using std::swap;
using std::vector;
using DutchFlag::Color ;

// @include
namespace DutchFlag_slow {

    void DutchFlagPartition(int pivot_index, vector <Color> *A_ptr) {
        vector <Color> &A = *A_ptr;
        Color pivot = A[pivot_index];

        // First pass: group elements smaller than pivot.
        for (int i = 0; i < A.size(); ++i) {
            // Look for a smaller element.
            for (int j = i + 1; j < A.size(); ++j) {
                if (A[j] < pivot) {
                    swap(A[i], A[j]);
                    break;
                }
            }
        }

        // Second pass: group elements larger than pivot.
        for (int i = A.size() - 1; i >= 0 && A[i] >= pivot; --i) {
            // Look for a larger element. Stop when we reach an element less
            // than pivot, since first pass has moved them to the start of A.
            for (int j = i - 1; j >= 0 && A[j] >= pivot; --j) {
                if (A[j] > pivot) {
                    swap(A[i], A[j]);
                    break;
                }
            }
        }
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_SLOW_INPLACE_H
