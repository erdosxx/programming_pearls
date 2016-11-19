#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_CIRCULAR_ARRAY_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_CIRCULAR_ARRAY_H
// 12.3 Search a cyclically sorted array

#include <vector>

using std::vector;

namespace distinct {

    // for cyclically ascending sorted array
    int SearchSmallest(const vector<int> &A) {
        int left = 0;
        int right = A.size() - 1;

        while (left < right) {
            int mid = left + ((right - left) / 2);

            if (A[mid] > A[right]) {
                // Minimum must be in [mid + 1 : right].
                left = mid + 1;
            } else {  // A[mid] < A[right].
                // Minimum cannot be in [mid + 1 : right] so it must be in [left : mid].
                right = mid;
            }
        }
        // Loop ends when left == right.
        return right;
    }

}

#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_CIRCULAR_ARRAY_H
