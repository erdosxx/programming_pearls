#ifndef ALGORITHM_ANALYSIS_INTEGER_TO_ROMAN_H
#define ALGORITHM_ANALYSIS_INTEGER_TO_ROMAN_H
// 7.9.2 Variant Convert from Roman to decimal

#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <functional>

using std::array;
using std::string;
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::greater;

void append_roman_chars(const int& digit, const size_t& idx, const array<char, 9>& kSymbols,
                        string* ret_ptr) {
    string& ret = *ret_ptr;

    if (digit == 0) {
        return;
    } else if (digit <= 3) {
        // append digit copies of char kSymbols[idx]
        ret.append(digit, kSymbols[idx]);
    } else if (digit == 4) {
        ret.push_back(kSymbols[idx]);
        ret.push_back(kSymbols[idx - 1]);
    } else if (digit <= 8) {
        ret.push_back(kSymbols[idx - 1]);
        ret.append(digit - 5, kSymbols[idx]);
    } else {  // digit == 9.
        ret.push_back(kSymbols[idx]);
        ret.push_back(kSymbols[idx - 2]);
    }
}

// This function only work uptp 3999
string int_to_roman(int n) {
    // kSymbols represents {1000, 500, 100, 50, 10, 5, 1}.
    const array<char, 9> kSymbols = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
    int scale = 1000;
    string ret;

    for (size_t i = 0; n && i < kSymbols.size(); i += 2) {
        append_roman_chars(n / scale, i, kSymbols, &ret);
        n %= scale;
        scale /= 10;
    }
    return ret;
}

using citer_type = map<int, string, greater<>>::const_iterator;

string int_to_roman_erdos(int n) {
    map<int, string, greater<>> roman_str = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
            {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"},
            {5, "V"}, {4, "IV"}, {1, "I"}
    };

    string ret;

    for (citer_type iter = roman_str.cbegin(); iter != roman_str.cend(); ++iter) {
        int q = n / iter->first;

        while (q-- > 0) {
            ret += iter->second;
        }

        n %= iter->first;
    }

    return ret;
}

#endif //ALGORITHM_ANALYSIS_INTEGER_TO_ROMAN_H
