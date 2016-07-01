#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_AI_I_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_AI_I_H

#include <vector>

using std::vector;

// @include
int SearchEntryEqualToItsIndex(const vector<int>& A) {
    int low = 0, high = A.size() - 1;
    while (low <= high) {
        int mid = low + ((high - low) / 2);
        int difference = A[mid] - mid;
        // A[mid] == mid if and only if difference == 0.
        if (difference == 0) {
            return mid;
        } else if (difference > 0) {
            high = mid - 1;
        } else {  // difference < 0.
            low = mid + 1;
        }
    }
    return -1;
}
// @exclude

// O(n) way to find ans.
int CheckAns(const vector<int>& A) {
    for (size_t i = 0; i < A.size(); ++i) {
        if (A[i] == static_cast<int>(i)) {
            return static_cast<int>(i);
        }
    }
    return -1;
}


#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_AI_I_H
