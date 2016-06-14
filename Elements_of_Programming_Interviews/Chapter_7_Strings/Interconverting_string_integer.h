#ifndef ALGORITHM_ANALYSIS_INTERCONVERTING_STRING_INTEGER_H
#define ALGORITHM_ANALYSIS_INTERCONVERTING_STRING_INTEGER_H

#include <algorithm>
#include <cctype>
#include <random>
#include <string>

using std::default_random_engine;
using std::invalid_argument;
using std::random_device;
using std::string;
using std::uniform_int_distribution;

string RandIntString(int len) {
    default_random_engine gen((random_device())());
    string ret;
    if (len == 0) {
        return {"0"};
    }

    uniform_int_distribution<int> pos_or_neg(0, 1);
    if (pos_or_neg(gen)) {
        ret.push_back('-');
    }

    uniform_int_distribution<int> num_dis('1', '9');
    ret.push_back(num_dis(gen));

    while (--len) {
        uniform_int_distribution<int> dis('0', '9');
        ret.push_back(dis(gen));
    }

    return ret;
}

// @include
string IntToString(int x) {
    bool is_negative = false;
    if (x < 0) {
        x = -x, is_negative = true;
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
