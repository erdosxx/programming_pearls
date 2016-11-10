#ifndef ALGORITHM_ANALYSIS_MINIMUM_DISTANCE_3_SORTED_ARRAYS_H
#define ALGORITHM_ANALYSIS_MINIMUM_DISTANCE_3_SORTED_ARRAYS_H
// 15.6 Find the closest entries in three sorted arrays

#include <algorithm>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>

using std::max;
using std::min;
using std::multimap;
using std::next;
using std::numeric_limits;
using std::pair;
using std::set;
using std::vector;

// @include
int FindClosestElementsInSortedArrays(
        const vector<vector<int>>& sorted_arrays) {
    int min_distance_so_far = numeric_limits<int>::max();

    struct IterTail {
        vector<int>::const_iterator iter, tail;
    };
    // Stores two iterators in each entry. One for traversing, and the other to
    // check we reach the end.

    // multimap: sort <int, IterTail> pair in ascending order.
    // Multimaps are associative containers that store elements formed
    // by a combination of a key value and a mapped value, following a specific order,
    // and where multiple elements can have equivalent keys.
    multimap<int, IterTail> iter_and_tail;
    for (const vector<int>& sorted_array : sorted_arrays) {
        iter_and_tail.emplace(
                sorted_array.front(),
                IterTail{sorted_array.cbegin(), sorted_array.cend()});
    }

    while (true) {
        int min_value = iter_and_tail.cbegin()->first;
        int max_value = iter_and_tail.crbegin()->first;
        min_distance_so_far = min(max_value - min_value, min_distance_so_far);

        const auto next_min = next(iter_and_tail.cbegin()->second.iter);
        const auto next_end = iter_and_tail.cbegin()->second.tail;
        // Return if some array has no remaining elements.
        if (next_min == next_end) {
            return min_distance_so_far;
        }
        iter_and_tail.emplace(*next_min, IterTail{next_min, next_end});
        iter_and_tail.erase(iter_and_tail.cbegin());
    }
}
// @exclude

int Distance(const vector<vector<int>>& sorted_arrays,
             const vector<int>& idx) {
    int max_val = numeric_limits<int>::min();
    int min_val = numeric_limits<int>::max();

    for (int i = 0; i < idx.size(); ++i) {
        max_val = max(max_val, sorted_arrays[i][idx[i]]);
        min_val = min(min_val, sorted_arrays[i][idx[i]]);
    }
    return max_val - min_val;
}

void RecGenAnswer(const vector<vector<int>>& sorted_arrays, vector<int>& idx,
                  int level, int* ans) {
    if (level == sorted_arrays.size()) {
        *ans = min(Distance(sorted_arrays, idx), *ans);
        return;
    }
    for (int i = 0; i < sorted_arrays[level].size(); ++i) {
        idx[level] = i;
        RecGenAnswer(sorted_arrays, idx, level + 1, ans);
    }
}

int BruteForceGenAnswer(const vector<vector<int>>& sorted_arrays) {
    int ans = numeric_limits<int>::max();
    vector<int> idx(sorted_arrays.size());
    RecGenAnswer(sorted_arrays, idx, 0, &ans);
    // cout << ans << endl;
    return ans;
}

#endif //ALGORITHM_ANALYSIS_MINIMUM_DISTANCE_3_SORTED_ARRAYS_H
