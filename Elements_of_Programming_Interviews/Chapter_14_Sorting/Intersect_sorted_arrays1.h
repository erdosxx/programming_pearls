#ifndef ALGORITHM_ANALYSIS_INTERSECT_SORTED_ARRAYS1_H
#define ALGORITHM_ANALYSIS_INTERSECT_SORTED_ARRAYS1_H
// 14.1 Compute the intersection of two sorted arrays

#include <vector>

using std::vector;

namespace IntersectTwoSortedArrays1 {

    // Brute-force approach O(mn)
    vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                         const vector<int>& B) {
        vector<int> insersection_A_B;
        for (int i = 0; i < A.size(); ++i) {
            if (i == 0 || A[i] != A[i - 1]) {
                for (auto b : B) {
                    if (A[i] == b) {
                        insersection_A_B.emplace_back(A[i]);
                        break;
                    }
                }
            }
        }
        return insersection_A_B;
    }

}  // namespace IntersectTwoSortedArrays1


#endif //ALGORITHM_ANALYSIS_INTERSECT_SORTED_ARRAYS1_H
