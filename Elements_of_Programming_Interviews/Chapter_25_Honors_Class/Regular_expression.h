#ifndef ALGORITHM_ANALYSIS_REGULAR_EXPRESSION_H
#define ALGORITHM_ANALYSIS_REGULAR_EXPRESSION_H

#include <string>

using std::string;

bool IsMatchHere(const string &, int, const string &, int);

// @include
bool IsMatch(const string &regex, const string &s) {
    // Case (2.): regex starts with '^'.
    if (regex.front() == '^') {
        return IsMatchHere(regex, 1, s, 0);
    }

    for (int i = 0; i <= s.size(); ++i) {
        if (IsMatchHere(regex, 0, s, i)) {
            return true;
        }
    }
    return false;
}

bool IsMatchHere(const string &regex, int regex_offset, const string &s,
                 int s_offset) {
    if (regex_offset == regex.size()) {
        // Case (1.): Empty regex matches all strings.
        return true;
    }

    if (regex_offset == regex.size() - 1 && regex[regex_offset] == '$') {
        // Case (2.): Reach the end of regex, and last char is '$'.
        return s_offset == s.size();
    }

    if (regex_offset <= regex.size() - 2 && regex[regex_offset + 1] == '*') {
        // Case (3.): A '*' match.
        // Iterate through s, checking '*' condition, if '*' condition holds,
        // performs the remaining checks.
        for (int i = s_offset + 1;
             i < s.size() &&
             (regex[regex_offset] == '.' || regex[regex_offset] == s[i - 1]);
             ++i) {
            if (IsMatchHere(regex, regex_offset + 2, s, i)) {
                return true;
            }
        }
        // See '*' matches zero character in s[s_offset : s.size() - 1].
        return IsMatchHere(regex, regex_offset + 2, s, s_offset);
    }

    // Case (4.): regex begins with single character match.
    return s_offset < s.size() &&
           (regex[regex_offset] == '.' || regex[regex_offset] == s[s_offset]) &&
           IsMatchHere(regex, regex_offset + 1, s, s_offset + 1);
}
// @exclude

#endif //ALGORITHM_ANALYSIS_REGULAR_EXPRESSION_H
