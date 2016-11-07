#ifndef ALGORITHM_ANALYSIS_3_SUM_H
#define ALGORITHM_ANALYSIS_3_SUM_H
// 18.4 The 3-sum problem

#include <algorithm>
#include <vector>

#include "2_sum.h"

using TwoSum::HasTwoSum;
using std::vector;

// @include
bool HasThreeSum(vector<int> A, int t) {
    sort(A.begin(), A.end());

    for (int a : A) {
        // Finds if the sum of two numbers in A equals to t - a.
        if (HasTwoSum(A, t - a)) {
            return true;
        }
    }
    return false;
}
// @exclude

// n^3 solution.


#endif //ALGORITHM_ANALYSIS_3_SUM_H
