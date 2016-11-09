#ifndef ALGORITHM_ANALYSIS_LONGEST_VALID_PARENTHESES_H
#define ALGORITHM_ANALYSIS_LONGEST_VALID_PARENTHESES_H
// 25.11 Compute the longest substring with matching parens

#include <algorithm>
#include <stack>
#include <string>
#include <vector>

using std::max;
using std::stack;
using std::string;
using std::vector;

// @include
int LongestValidParentheses(const string& s) {
    int max_length = 0;
    int end = -1;
    stack<int> left_parentheses_indices;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            left_parentheses_indices.emplace(i);
        } else if (left_parentheses_indices.empty()) { // s[i] == ')' and stack is empty
            end = i;
        } else { // s[i] == ')' and stack is NOT empty
            left_parentheses_indices.pop();
            int start = left_parentheses_indices.empty()
                        ? end
                        : left_parentheses_indices.top();
            max_length = max(max_length, i - start);
        }
    }
    return max_length;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_LONGEST_VALID_PARENTHESES_H
