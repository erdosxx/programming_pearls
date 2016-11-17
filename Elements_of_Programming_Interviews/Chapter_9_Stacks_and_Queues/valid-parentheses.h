#ifndef ALGORITHM_ANALYSIS_VALID_PARENTHESES_H
#define ALGORITHM_ANALYSIS_VALID_PARENTHESES_H
// 9.3 Test a string over ‘’{,},(,),[,]’’ for well-formedness
// Amazon

#include <stack>
#include <string>

using std::stack;
using std::string;

// @include
bool IsWellFormed(const string& s) {
    stack<char> left_chars;

    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            left_chars.emplace(s[i]);
        } else {
            if (left_chars.empty()) {  // for the case "}" or "]" or ")"
                return false;  // Unmatched right char.
            }

            if ((s[i] == ')' && left_chars.top() != '(') ||
                (s[i] == '}' && left_chars.top() != '{') ||
                (s[i] == ']' && left_chars.top() != '[')) {
                return false;  // Mismatched chars.
            }
            left_chars.pop();
        }
    }
    return left_chars.empty();
}
// @exclude

#endif //ALGORITHM_ANALYSIS_VALID_PARENTHESES_H
