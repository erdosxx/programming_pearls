#ifndef ALGORITHM_ANALYSIS_PERMUTATIONS_ALTERNATIVE_H
#define ALGORITHM_ANALYSIS_PERMUTATIONS_ALTERNATIVE_H
// 16.3 Generate permutations

#include <algorithm>
#include <string>
#include <vector>

using std::swap;
using std::vector;

namespace alt {
    void DirectedPermutations_upto_i(int i, vector<int>& A, vector<vector<int>> *result);

// @include
    vector<vector<int>> Permutations(vector<int> A) {
        vector<vector<int>> result;
        DirectedPermutations_upto_i(0, A, &result);
        return result;
    }

    void DirectedPermutations_upto_i(int i, vector<int>& A,
                                     vector<vector<int>> *result) {
        //vector<int> &A = *A_ptr;
        if (i == A.size() - 1) {
            result->emplace_back(A);
            return;
        }

        // Try every possibility for A[i].
        for (int j = i; j < A.size(); ++j) {
            swap(A[i], A[j]);
            // Generate all permutations for A[i + 1 : A.size() - 1].
            DirectedPermutations_upto_i(i + 1, A, result);
            swap(A[i], A[j]);
        }
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_PERMUTATIONS_ALTERNATIVE_H
