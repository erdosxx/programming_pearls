#ifndef ALGORITHM_ANALYSIS_SQUARE_ROOT_H
#define ALGORITHM_ANALYSIS_SQUARE_ROOT_H
// 12.5 Compute the real square root

#include <limits>

using std::numeric_limits;

using Ordering =  enum { SMALLER, EQUAL, LARGER };

// for comparison of double data.
// EQUAL:  -Epsilon <= diff <= Epsilon
//          Epsilon = 2.22045e-16
Ordering Compare(double a, double b) {
    // Uses normalization for precision problem.
    double diff = (a - b) / b;
    return diff < -numeric_limits<double>::epsilon()
           ? SMALLER
           : diff > numeric_limits<double>::epsilon() ? LARGER : EQUAL;
}

double SquareRoot(double x) {
    // Decides the search range according to x's timestamp relative to 1.0.
    double left, right;
    if (x < 1.0) {
        left = x, right = 1.0;
    } else {  // x >= 1.0.
        left = 1.0, right = x;
    }

    // Keeps searching as long as left < right, within tolerance.
    while (Compare(left, right) == SMALLER) {
        double mid = left + (right - left)/2.0;
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

#endif //ALGORITHM_ANALYSIS_SQUARE_ROOT_H
