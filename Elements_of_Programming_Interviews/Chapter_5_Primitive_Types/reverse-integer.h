#ifndef ALGORITHM_ANALYSIS_REVERSE_INTEGER_H
#define ALGORITHM_ANALYSIS_REVERSE_INTEGER_H
// 5.8 Reverse digits

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <string>

using std::stoi;
using std::stol;
using std::string;
using std::to_string;

// @include
long Reverse(int x) {
    bool is_negative = x < 0;
    long result = 0, x_remaining = abs(x);
    while (x_remaining) {
        result = result * 10 + x_remaining % 10;
        x_remaining /= 10;
    }
    return is_negative ? -result : result;
}
// @exclude

long CheckAns(int x) {
    string s = to_string(x);
    if (s.front() == '-') {
        reverse(s.begin() + 1, s.end());
    } else {
        reverse(s.begin(), s.end());
    }
    return stol(s);
}

#endif //ALGORITHM_ANALYSIS_REVERSE_INTEGER_H
