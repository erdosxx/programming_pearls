#ifndef ALGORITHM_ANALYSIS_RUN_LENGTH_COMPRESSION_H
#define ALGORITHM_ANALYSIS_RUN_LENGTH_COMPRESSION_H
// 7.12 Implement run-length encoding

#include <cctype>
#include <cstdlib>
#include <string>

using std::string;
using std::to_string;

// 3e4f2e -> eeeffffee
string Decoding(const string &s) {
    int count = 0;
    string result;

    for (const char &c : s) {
        if (isdigit(c)) {
            count = count * 10 + c - '0';
        } else {  // c is a letter of alphabet.
            result.append(count, c);  // Appends count copies of c to result.
            count = 0;
        }
    }
    return result;
}

// eeeffffee -> 3e4f2e
string Encoding(const string &s) {
    string result;

    int count = 1;

    for (int i = 1; i <= s.size(); ++i) {
        if (i == s.size() || s[i] != s[i - 1]) {
            // Found new character so write the count of previous character.
            result += to_string(count) + s[i - 1];
            count = 1;
        } else {  // s[i] == s[i - 1].
            ++count;
        }
    }
    return result;
}

#endif //ALGORITHM_ANALYSIS_RUN_LENGTH_COMPRESSION_H
