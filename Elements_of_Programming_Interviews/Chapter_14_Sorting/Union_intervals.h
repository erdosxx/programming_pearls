#ifndef ALGORITHM_ANALYSIS_UNION_INTERVALS_H
#define ALGORITHM_ANALYSIS_UNION_INTERVALS_H

#include <algorithm>
#include <vector>

using std::vector;

// @include
namespace p_14_6 {
    class Interval {
    private:
        struct Endpoint {
            bool isClosed;
            int val;
        };

    public:
        bool operator<(const Interval &i) const {
            if (left.val != i.left.val) {
                return left.val < i.left.val;
            }
            // Left endpoints are equal, so now see if one is closed and the other
            // open
            // - closed intervals should appear first.
            return left.isClosed && !i.left.isClosed;
        }

        Endpoint left, right;
    };

    vector<Interval> UnionOfIntervals(vector<Interval> intervals) {
        // Empty input.
        if (intervals.empty()) {
            return {};
        }

        // Sort intervals according to left endpoints of intervals.
        sort(intervals.begin(), intervals.end());
        Interval curr(intervals.front());
        vector<Interval> result;

        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i].left.val < curr.right.val ||
                (intervals[i].left.val == curr.right.val &&
                 (intervals[i].left.isClosed || curr.right.isClosed))) {
                if (intervals[i].right.val > curr.right.val ||
                    (intervals[i].right.val == curr.right.val &&
                     intervals[i].right.isClosed)) {
                    curr.right = intervals[i].right;
                }
            } else {
                result.emplace_back(curr);
                curr = intervals[i];
            }
        }
        result.emplace_back(curr);
        return result;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_UNION_INTERVALS_H
