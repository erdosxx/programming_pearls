#ifndef ALGORITHM_ANALYSIS_LOOK_AND_SAY_H
#define ALGORITHM_ANALYSIS_LOOK_AND_SAY_H
// 7.8 The look-and-say problem

#include <algorithm>
#include <string>

using std::string;
using std::to_string;

string NextNumber(const string& s);

string LookAndSay(int n) {
    string s = "1";
    for (int i = 1; i < n; ++i) {
        s = NextNumber(s);
    }
    return s;
}

string NextNumber(const string& s) {
    string ret;
    for (int i = 0; i < s.size(); ++i) {
        int count = 1;
        while (i + 1 < s.size() && s[i] == s[i + 1]) {
            ++i, ++count;
        }
        ret += to_string(count) + s[i];
    }
    return ret;
}

#endif //ALGORITHM_ANALYSIS_LOOK_AND_SAY_H
