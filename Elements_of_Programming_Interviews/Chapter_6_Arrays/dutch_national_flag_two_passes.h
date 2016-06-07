#ifndef ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_TWO_PASSES_H
#define ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_TWO_PASSES_H

#include <algorithm>
#include <vector>
#include "Dutch_national_flag.h"

using std::swap;
using std::vector;
using DutchFlag::Color ;

// @include
namespace DutchFlag_two {
    void DutchFlagPartition(int pivot_index, vector<Color> *A_ptr) {
        vector<Color> &A = *A_ptr;
        Color pivot = A[pivot_index];
        // First pass: group elements smaller than pivot.
        int smaller = 0;
        for (int i = 0; i < A.size(); ++i) {
            if (A[i] < pivot) {
                swap(A[i], A[smaller++]);
            }
        }
        // Second pass: group elements larger than pivot.
        int larger = A.size() - 1;
        for (int i = A.size() - 1; i >= 0 && A[i] >= pivot; --i) {
            if (A[i] > pivot) {
                swap(A[i], A[larger--]);
            }
        }
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_TWO_PASSES_H
