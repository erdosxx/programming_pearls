#ifndef ALGORITHM_ANALYSIS_SQUARE_ROOT_H
#define ALGORITHM_ANALYSIS_SQUARE_ROOT_H

#include <limits>

using std::numeric_limits;

// @include
using Ordering =  enum { SMALLER, EQUAL, LARGER };

// @exclude
Ordering Compare(double a, double b);
// @include
double SquareRoot(double x) {
    // Decides the search range according to x's value relative to 1.0.
    double left, right;
    if (x < 1.0) {
        left = x, right = 1.0;
    } else {  // x >= 1.0.
        left = 1.0, right = x;
    }

    // Keeps searching as long as left < right, within tolerance.
    while (Compare(left, right) == SMALLER) {
        double mid = left + 0.5 * (right - left);
        double mid_squared = mid * mid;
        if (Compare(mid_squared, x) == EQUAL) {
            return mid;
        } else if (Compare(mid_squared, x) == LARGER) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
}

Ordering Compare(double a, double b) {
    // Uses normalization for precision problem.
    double diff = (a - b) / b;
    return diff < -numeric_limits<double>::epsilon()
           ? SMALLER
           : diff > numeric_limits<double>::epsilon() ? LARGER : EQUAL;
}
// @exclude


#endif //ALGORITHM_ANALYSIS_SQUARE_ROOT_H
