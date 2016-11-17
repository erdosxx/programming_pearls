#ifndef ALGORITHM_ANALYSIS_CONVERT_BASE_H
#define ALGORITHM_ANALYSIS_CONVERT_BASE_H
// 7.2 Base conversion

#include <algorithm>
#include <string>

using std::string;

string ConstructFromBase(int x, int base) {
    return x == 0 ? "" : ConstructFromBase(x / base, base) +
                         (char)(x % base >= 10 ? 'A' + x % base - 10
                                               : '0' + x % base);
}

string ConvertBase(const string& s, int b1, int b2) {
    bool is_negative = s.front() == '-';

    int x = 0;
    for (size_t i = (is_negative == true ? 1 : 0); i < s.size(); ++i) {
        x *= b1;
        x += isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;
    }

    return (is_negative ? "-" : "") + (x == 0 ? "0" : ConstructFromBase(x, b2));
}

#endif //ALGORITHM_ANALYSIS_CONVERT_BASE_H
