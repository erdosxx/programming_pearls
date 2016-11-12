#ifndef ALGORITHM_ANALYSIS_SPREADSHEET_ENCODING_H
#define ALGORITHM_ANALYSIS_SPREADSHEET_ENCODING_H
// 7.3 Compute the spreadsheet column encoding

#include <string>

using std::string;

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
