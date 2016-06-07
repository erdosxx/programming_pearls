#ifndef ALGORITHM_ANALYSIS_PALINDROME_NUMBER_H
#define ALGORITHM_ANALYSIS_PALINDROME_NUMBER_H

#include <cmath>
#include <string>

using std::to_string;

// @include
bool IsPalindromeNumber(int x) {
    if (x < 0) {
        return false;
    } else if (x == 0) {
        return true;
    }

    const int num_digits = static_cast<int>(floor(log10(x))) + 1;

    int msd_mask = static_cast<int>(pow(10, num_digits - 1));

    for (int i = 0; i < (num_digits / 2); ++i) {
        if (x / msd_mask != x % 10) {
            return false;
        }
        x %= msd_mask;  // Remove the most significant digit of x.
        x /= 10;  // Remove the least significant digit of x.
        msd_mask /= 100;
    }
    return true;
}
// @exclude

namespace palindrome_number {
    bool CheckAns(int x) {
        auto s = to_string(x);
        for (size_t i = 0, j = s.size() - 1; i < j; ++i, --j) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }
}

#endif //ALGORITHM_ANALYSIS_PALINDROME_NUMBER_H
