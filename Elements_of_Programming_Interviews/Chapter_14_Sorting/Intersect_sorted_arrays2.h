#ifndef ALGORITHM_ANALYSIS_INTERSECT_SORTED_ARRAYS2_H
#define ALGORITHM_ANALYSIS_INTERSECT_SORTED_ARRAYS2_H
// 14.1 Compute the intersection of two sorted arrays

#include <algorithm>
#include <vector>

using std::vector;

// optimal for A.size() << B.size()
namespace IntersectTwoSortedArrays2 {

    vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                         const vector<int>& B) {
        vector<int> intersection_A_B;
        for (int i = 0; i < A.size(); ++i) {
            if ( (i == 0 || A[i] != A[i - 1]) && binary_search(B.cbegin(), B.cend(), A[i]) ) {
                intersection_A_B.emplace_back(A[i]);
            }
        }
        return intersection_A_B;
    }

}  // namespace IntersectTwoSortedArrays2

#endif //ALGORITHM_ANALYSIS_INTERSECT_SORTED_ARRAYS2_H
