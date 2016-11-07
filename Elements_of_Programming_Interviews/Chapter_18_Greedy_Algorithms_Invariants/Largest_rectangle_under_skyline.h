#ifndef ALGORITHM_ANALYSIS_LARGEST_RECTANGLE_UNDER_SKYLINE_H
#define ALGORITHM_ANALYSIS_LARGEST_RECTANGLE_UNDER_SKYLINE_H
// 18.8 Compute the largest rectangle under the skyline

#include <algorithm>
#include <stack>
#include <vector>

using std::max;
using std::stack;
using std::vector;

int CalculateLargestRectangleAlternative(const vector<int>& heights) {
    // Calculate L.
    stack<int> s;
    vector<int> Left;

    // get left limit for every i
    for (int i = 0; i < heights.size(); ++i) {
        // make height[i] max in stack
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
        }
        Left.emplace_back(s.empty() ? -1 : s.top());
        s.emplace(i);
    }

    // Clear stack for calculating R.
    while (!s.empty()) {
        s.pop();
    }

    // get right limit for every i
    vector<int> Right(heights.size());
    for (int i = heights.size() - 1; i >= 0; --i) {
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
        }

        Right[i] = s.empty() ? heights.size() : s.top();
        s.emplace(i);
    }

    // For each heights[i], find its maximum area include it.
    int max_rectangle_area = 0;
    for (int i = 0; i < heights.size(); ++i) {
        max_rectangle_area =
                max(max_rectangle_area, heights[i] * (Right[i] - Left[i] - 1));
    }
    return max_rectangle_area;
}

bool IsNewPillarOrReachEnd(const vector<int>&, int, int);

// @include
int CalculateLargestRectangle(const vector<int>& heights) {
    stack<int> pillar_indices;
    int max_rectangle_area = 0;

    for (int i = 0; i <= heights.size(); ++i) {
        if (!pillar_indices.empty() && i < heights.size() &&
            heights[i] == heights[pillar_indices.top()]) {
            // Replace earlier building with same height by current building. This
            // ensures the later buildings have the correct left endpoint.
            pillar_indices.pop();
            pillar_indices.emplace(i);
        }

        // By iterating to heights.size() instead of heights.size() - 1, we can
        // uniformly handle the computation for rectangle area here.
        while (!pillar_indices.empty() &&
               IsNewPillarOrReachEnd(heights, i, pillar_indices.top())) {
            int height = heights[pillar_indices.top()];
            pillar_indices.pop();
            int width = pillar_indices.empty() ? i : i - pillar_indices.top() - 1;
            max_rectangle_area = max(max_rectangle_area, height * width);
        }
        pillar_indices.emplace(i);
    }
    return max_rectangle_area;
}

bool IsNewPillarOrReachEnd(const vector<int>& heights, int curr_idx,
                           int last_pillar_idx) {
    return curr_idx < heights.size()
           ? heights[curr_idx] < heights[last_pillar_idx]
           : true;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_LARGEST_RECTANGLE_UNDER_SKYLINE_H
