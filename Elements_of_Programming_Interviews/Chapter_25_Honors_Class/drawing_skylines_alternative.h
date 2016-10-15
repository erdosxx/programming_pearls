#ifndef ALGORITHM_ANALYSIS_DRAWING_SKYLINES_ALTERNATIVE_H
#define ALGORITHM_ANALYSIS_DRAWING_SKYLINES_ALTERNATIVE_H

#include <algorithm>
#include <vector>

using std::max;
using std::min;
using std::numeric_limits;
using std::vector;

namespace alt {

// @include
    struct Rectangle {
        int left, right, height;
    };
    using Skyline = vector<Rectangle>;

    Skyline ComputeSkyline(const vector<Rectangle> &buildings) {
        int min_left = numeric_limits<int>::max();
        int max_right = numeric_limits<int>::min();

        for (const Rectangle &building : buildings) {
            min_left = min(min_left, building.left);
            max_right = max(max_right, building.right);
        }

        vector<int> heights(max_right - min_left + 1, 0);
        for (const Rectangle &building : buildings) {
            for (int i = building.left; i <= building.right; ++i) {
                heights[i - min_left] = max(heights[i - min_left], building.height);
            }
        }

        Skyline result;
        int left = 0;
        for (int i = 1; i < heights.size(); ++i) {
            if (heights[i] != heights[i - 1]) {
                result.emplace_back(
                        Rectangle{left + min_left, i - 1 + min_left, heights[i - 1]});
                left = i;
            }
        }
        result.emplace_back(Rectangle{left + min_left, max_right, heights.back()});
        return result;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_DRAWING_SKYLINES_ALTERNATIVE_H
