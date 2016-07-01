#ifndef ALGORITHM_ANALYSIS_SQUARE_ROOT_INT_H
#define ALGORITHM_ANALYSIS_SQUARE_ROOT_INT_H

// @include
int SquareRoot(int k) {
    int left = 0, right = k;
    // Candidate interval [left, right] where everything before left has
    // square <= k, and everything after right has square > k.
    while (left <= right) {
        long mid = left + ((right - left) / 2);
        long mid_squared = mid * mid;
        if (mid_squared <= k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left - 1;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SQUARE_ROOT_INT_H
