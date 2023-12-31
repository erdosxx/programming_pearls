#ifndef ALGORITHM_ANALYSIS_UNION_INTERVALS_H
#define ALGORITHM_ANALYSIS_UNION_INTERVALS_H
// 14.6 Compute the union of intervals

#include <algorithm>
#include <vector>

using std::vector;

namespace p_14_6 {
    class Interval {
    private:
        struct Endpoint {
            bool isClosed;
            int val;
        };

    public:
        bool operator<(const Interval& that) const {
            if (left.val != that.left.val) {
                return left.val < that.left.val;
            }
            // Left endpoints are equal, so now see if one is closed and the other
            // open
            // - closed intervals should appear first.
            return left.isClosed && !that.left.isClosed;
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
            //   curr ---]  [--- intervals[i]
            if (intervals[i].left.val < curr.right.val ||
                (intervals[i].left.val == curr.right.val &&
                 (intervals[i].left.isClosed || curr.right.isClosed))) { // if curr and intervals[i] are connected
                if (intervals[i].right.val > curr.right.val ||
                    (intervals[i].right.val == curr.right.val &&
                     intervals[i].right.isClosed)) {
                    curr.right = intervals[i].right;
                }
            } else { // curr and intervals[i] are disconnected.
                result.emplace_back(curr);
                curr = intervals[i];
            }
        }
        result.emplace_back(curr);
        return result;
    }
}

#endif //ALGORITHM_ANALYSIS_UNION_INTERVALS_H
