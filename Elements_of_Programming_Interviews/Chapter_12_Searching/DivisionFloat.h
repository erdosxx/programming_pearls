#ifndef ALGORITHM_ANALYSIS_DIVISIONFLOAT_H
#define ALGORITHM_ANALYSIS_DIVISIONFLOAT_H
// 12.5.1 Variant Compute the real square root
#include "Square_root.h"

double division_no_operator(double x, double y) {
    double left, right;
    if (y < 1) {
        left = x, right = numeric_limits<double>::max();
    } else {
        left = 0, right = x;
    }

    while (Compare(left, right) == SMALLER) {  // left <= right
        double mid = left + 0.5 * (right - left);
        if (Compare(mid * y, x) == EQUAL) {  // x == mid * y, found answer
            return mid;
        } else if (Compare(mid * y, x) == LARGER) {  // x < mid * y
            right = mid;
        } else {  // x > mid * y
            left = mid;
        }
    }
    return left;
}

#endif //ALGORITHM_ANALYSIS_DIVISIONFLOAT_H
