#ifndef ALGORITHM_ANALYSIS_2_SUM_H
#define ALGORITHM_ANALYSIS_2_SUM_H
// 18.4 Variant The 3-sum problem

namespace TwoSum {

#include <vector>

    using std::vector;

// @include
    bool HasTwoSum(vector<int> A, int t) {
        int i = 0, j = A.size() - 1;
        while (i <= j) {
            if (A[i] + A[j] == t) {
                return true;
            } else if (A[i] + A[j] < t) {
                ++i;
            } else {  // A[i] + A[j] > t.
                --j;
            }
        }
        return false;
    }
// @exclude

}  // namespace TwoSum

#endif //ALGORITHM_ANALYSIS_2_SUM_H
