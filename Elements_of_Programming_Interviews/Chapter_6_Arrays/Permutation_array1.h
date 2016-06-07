#ifndef ALGORITHM_ANALYSIS_PERMUTATION_ARRAY1_H
#define ALGORITHM_ANALYSIS_PERMUTATION_ARRAY1_H

#include <algorithm>
#include <vector>

using std::swap;
using std::vector;

namespace ApplyPermutation1 {

// @include
    void ApplyPermutation(vector<int>* perm_ptr, vector<int>* A_ptr) {
        vector<int> &perm = *perm_ptr;
        vector<int> &A = *A_ptr;

        for (int i = 0; i < A.size(); ++i) {
            // Check if the element at index i has not been moved by checking if
            // perm[i] is nonnegative.
            int next = i;
            while (perm[next] >= 0) {
                swap(A[i], A[perm[next]]);
                int temp = perm[next];
                // Subtracts perm.size() from an entry in perm to make it negative,
                // which
                // indicates the corresponding move has been performed.
                perm[next] -= A.size(); // For 0 in perm, we cannot use -1* perm for this.
                next = temp;
            }
        }

        // Restore perm.
        for_each(perm.begin(), perm.end(), [&](int& x) { x += A.size(); });
    }
// @exclude

}  // ApplyPermutation1

#endif //ALGORITHM_ANALYSIS_PERMUTATION_ARRAY1_H
