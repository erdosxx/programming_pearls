#ifndef ALGORITHM_ANALYSIS_K_TH_LARGEST_ELEMENT_LARGE_N_H
#define ALGORITHM_ANALYSIS_K_TH_LARGEST_ELEMENT_LARGE_N_H
// 25.17 Find the kth largest element - large n, small k

#include <algorithm>
#include <functional>
#include <sstream>
#include <vector>

using std::greater;
using std::istringstream;
using std::stringstream;
using std::vector;

// @include
int FindKthLargestUnknownLength(istringstream* sin, int k) {
    vector<int> candidates;
    int x;

    while (*sin >> x) {
        candidates.emplace_back(x);
        if (candidates.size() == 2 * k - 1) {
            // Reorders elements about median with larger elements appearing before
            // the median.
            nth_element(candidates.begin(), candidates.begin() + k - 1,
                        candidates.end(), greater<int>());
            // Reset idx to keep just the k largest elements seen so far.
            candidates.resize(k);
        }
    }
    // Finds the k-th largest element in candidates.
    nth_element(candidates.begin(), candidates.begin() + k - 1,
                candidates.end(), greater<int>());
    return candidates[k - 1];
}
// @exclude

#endif //ALGORITHM_ANALYSIS_K_TH_LARGEST_ELEMENT_LARGE_N_H
