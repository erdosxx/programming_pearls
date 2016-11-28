#ifndef ALGORITHM_ANALYSIS_ROMAN_TO_INTEGER_H
#define ALGORITHM_ANALYSIS_ROMAN_TO_INTEGER_H
// 7.9 Convert from Roman to decimal

#include <algorithm>
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

int RomanToInteger(const string& s) {
    unordered_map<char, int> T = {{'I', 1},   {'V', 5},   {'X', 10},  {'L', 50},
                                  {'C', 100}, {'D', 500}, {'M', 1000}};

    int sum = T[s.back()];
    for (int i = s.length() - 2; i >= 0; --i) {
        if (T[s[i]] < T[s[i + 1]]) { // ex, IV -> 5-1 = 4
            sum -= T[s[i]];
        } else {
            sum += T[s[i]];
        }
    }
    return sum;
}

#endif //ALGORITHM_ANALYSIS_ROMAN_TO_INTEGER_H
