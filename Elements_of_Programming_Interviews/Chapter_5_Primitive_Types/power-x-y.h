#ifndef ALGORITHM_ANALYSIS_POWER_X_Y_H
#define ALGORITHM_ANALYSIS_POWER_X_Y_H
// 5.7 Compute x^y

#include <algorithm>
#include <cmath>

// 0 means equal, -1 means smaller, and 1 means larger.
namespace power {
    int Compare(double a, double b) {
        // Uses normalization for precision problem.
        double diff = (a - b) / b;
        return diff < -1.0e-9 ? -1 : diff > 1.0e-9;
    }
}

// @include
double Power(double x, int y) {
    double result = 1.0;
    long long power = y;

    if (y < 0) {
        power = -power;
        x = 1.0 / x;
    }

    while (power) {
        if (power & 1) {
            result *= x;
        }
        x *= x;
        power >>= 1;
    }
    return result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_POWER_X_Y_H
