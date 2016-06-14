#ifndef ALGORITHM_ANALYSIS_SPREADSHEET_ENCODING_H
#define ALGORITHM_ANALYSIS_SPREADSHEET_ENCODING_H

#include <string>

using std::string;

string RandString(int len) {
    default_random_engine gen((random_device())());
    string ret;
    uniform_int_distribution<int> dis('A', 'Z');
    while (len--) {
        ret.push_back(dis(gen));
    }
    return ret;
}

// @include
int SSDecodeColID(const string& col) {
    int ret = 0;
    for (char c : col) {
        ret = ret * 26 + c - 'A' + 1;
    }
    return ret;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SPREADSHEET_ENCODING_H
