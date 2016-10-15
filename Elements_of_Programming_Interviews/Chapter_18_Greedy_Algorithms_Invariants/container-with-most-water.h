#ifndef ALGORITHM_ANALYSIS_CONTAINER_WITH_MOST_WATER_H
#define ALGORITHM_ANALYSIS_CONTAINER_WITH_MOST_WATER_H

#include <algorithm>
#include <string>
#include <vector>

using std::max;
using std::min;
using std::vector;

// @include
int GetMaxTrappedWater(const vector<int>& heights) {
    int left = 0;
    int right = heights.size() - 1;
    int max_water = 0;

    while (left < right) {
        int width = right - left;
        max_water = max(max_water, width * min(heights[left], heights[right]));

        if (heights[left] > heights[right]) {
            --right;
        } else if (heights[left] < heights[right]) {
            ++left;
        } else {  // heights[i] == heights[j].
            ++left, --right;
        }
    }
    return max_water;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_CONTAINER_WITH_MOST_WATER_H
