#ifndef ALGORITHM_ANALYSIS_INSERT_INTERVAL_H
#define ALGORITHM_ANALYSIS_INSERT_INTERVAL_H

#include <algorithm>
#include <string>
#include <vector>

using std::max;
using std::min;
using std::vector;

// @include
struct Interval {
    int left, right;
};

vector<Interval> AddInterval(const vector<Interval>& disjoint_intervals,
                             Interval new_interval) {
    size_t i = 0;
    vector<Interval> result;

    // Processes intervals in disjoint_intervals which come before new_interval.
    while (i < disjoint_intervals.size() &&
           new_interval.left > disjoint_intervals[i].right) {
        result.emplace_back(disjoint_intervals[i++]);
    }

    // Processes intervals in disjoint_intervals which overlap with
    // new_interval.
    while (i < disjoint_intervals.size() &&
           new_interval.right >= disjoint_intervals[i].left) {
        // If [a, b] and [c, d] overlap, their union is [min(a, c),max(b, d)].
        new_interval = {min(new_interval.left, disjoint_intervals[i].left),
                        max(new_interval.right, disjoint_intervals[i].right)};
        ++i;
    }
    result.emplace_back(new_interval);

    // Processes intervals in disjoint_intervals which come after new_interval.
    result.insert(result.end(), disjoint_intervals.begin() + i,
                  disjoint_intervals.end());
    return result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_INSERT_INTERVAL_H
