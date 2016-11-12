#ifndef ALGORITHM_ANALYSIS_INTERCONVERTING_STRING_INTEGER_H
#define ALGORITHM_ANALYSIS_INTERCONVERTING_STRING_INTEGER_H
// 7.1 Interconvert strings and integers

#include <algorithm>
#include <string>

using std::string;

// @include
string IntToString(int x) {
    bool is_negative = false;

    if (x < 0) {
        x = -x;
        is_negative = true;
    }

    string s;
    do {
        s += '0' + x % 10;
        x /= 10;
    } while (x);

    if (is_negative) {
        s += '-';  // Adds the negative sign back.
    }

    reverse(s.begin(), s.end());
    return s;
}

int StringToInt(const string& s) {
    bool is_negative = s[0] == '-';

    int result = 0;
    for (int i = s[0] == '-' ? 1 : 0; i < s.size(); ++i) {
        int digit = s[i] - '0';
        result = result * 10 + digit;
    }
    return is_negative ? -result : result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_INTERCONVERTING_STRING_INTEGER_H
