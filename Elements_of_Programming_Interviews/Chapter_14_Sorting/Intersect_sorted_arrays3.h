#ifndef ALGORITHM_ANALYSIS_INTERSECT_SORTED_ARRAYS3_H
#define ALGORITHM_ANALYSIS_INTERSECT_SORTED_ARRAYS3_H
// 14.1 Compute the intersection of two sorted arrays

#include <vector>

using std::vector;

namespace IntersectTwoSortedArrays3 {

    vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                         const vector<int>& B) {
        vector<int> intersection_A_B;
        int i = 0, j = 0;

        while (i < A.size() && j < B.size()) {
            if (A[i] == B[j] && (i == 0 || A[i] != A[i - 1])) {
                intersection_A_B.emplace_back(A[i]);
                ++i, ++j;
            } else if (A[i] < B[j]) {
                ++i;
            } else {  // A[i] > B[j] or A[i] == B[j] && A[i] == A[i-1]
                ++j;
            }
        }
        return intersection_A_B;
    }

}  // namespace IntersectTwoSortedArrays3

#endif //ALGORITHM_ANALYSIS_INTERSECT_SORTED_ARRAYS3_H
