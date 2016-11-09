#ifndef ALGORITHM_ANALYSIS_TRAPPING_RAIN_WATER_H
#define ALGORITHM_ANALYSIS_TRAPPING_RAIN_WATER_H
// 25.35 Trapping water

#include <algorithm>
#include <utility>
#include <vector>

using std::vector;

// @include
int CalculateTrappingWater(const vector<int> &A) {
    if (A.empty()) {
        return 0;
    }

    // Finds the index with maximum height.
    int max_h = distance(A.cbegin(), max_element(A.cbegin(), A.cend()));

    // Calculates the water within [1 : max_h - 1].
    int sum = 0;
    int left = A.front();

    for (int i = 1; i < max_h; ++i) {
        if (A[i] >= left) {
            left = A[i];
        } else {
            sum += left - A[i];
        }
    }

    // Calculates the water within [max_h + 1 : A.size() - 2].
    int right = A.back();
    for (int i = A.size() - 2; i > max_h; --i) {
        if (A[i] >= right) {
            right = A[i];
        } else {
            sum += right - A[i];
        }
    }
    return sum;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_TRAPPING_RAIN_WATER_H
