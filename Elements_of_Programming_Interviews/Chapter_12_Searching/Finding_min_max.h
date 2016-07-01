#ifndef ALGORITHM_ANALYSIS_FINDING_MIN_MAX_H
#define ALGORITHM_ANALYSIS_FINDING_MIN_MAX_H

#include <algorithm>
#include <utility>
#include <vector>

using std::max;
using std::min;
using std::minmax;
using std::pair;
using std::vector;

// @include
struct MinMax {
    int min, max;
};

MinMax FindMinMax(const vector<int>& A) {
    if (A.size() <= 1) {
        return {A.front(), A.front()};
    }

    pair<int, int> global_min_max = minmax(A[0], A[1]);
    // Process two elements at a time.
    for (int i = 2; i + 1 < A.size(); i += 2) {
        pair<int, int> local_min_max = minmax(A[i], A[i + 1]);
        global_min_max = {min(global_min_max.first, local_min_max.first),
                          max(global_min_max.second, local_min_max.second)};
    }
    // If there is odd number of elements in the array, we still
    // need to compare the last element with the existing answer.
    if (A.size() % 2) {
        global_min_max = {min(global_min_max.first, A.back()),
                          max(global_min_max.second, A.back())};
    }
    return {global_min_max.first, global_min_max.second};
}
// @exclude

#endif //ALGORITHM_ANALYSIS_FINDING_MIN_MAX_H
