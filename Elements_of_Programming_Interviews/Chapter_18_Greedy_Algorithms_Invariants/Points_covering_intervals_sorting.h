#ifndef ALGORITHM_ANALYSIS_POINTS_COVERING_INTERVALS_SORTING_H
#define ALGORITHM_ANALYSIS_POINTS_COVERING_INTERVALS_SORTING_H
// 18.3 The interval covering problem

#include <algorithm>
#include <vector>

using std::vector;

namespace sorting {

// @include
    struct Interval {
        int left, right;
    };

    vector<int> FindMinimumVisits(vector <Interval> intervals) {
        if (intervals.empty()) {
            return {};
        }

        // Sort intervals based on the right endpoints.
        sort(intervals.begin(), intervals.end(),
             [](const Interval &a, const Interval &b) -> bool {
                 return a.right < b.right;
             });

        vector<int> visits;

        int last_visit_time = intervals.front().right;

        visits.emplace_back(last_visit_time);

        for (const Interval &interval : intervals) {
            if (interval.left > last_visit_time) {
                // The current right endpoint, last_visit_time, will not cover any more
                // intervals.
                last_visit_time = interval.right;
                visits.emplace_back(last_visit_time);
            }
        }
        return visits;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_POINTS_COVERING_INTERVALS_SORTING_H
