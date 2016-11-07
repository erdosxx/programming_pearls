#ifndef ALGORITHM_ANALYSIS_GENERATE_PARENTHESES_H
#define ALGORITHM_ANALYSIS_GENERATE_PARENTHESES_H
// 16.6 Generate strings of matched parens

#include <algorithm>
#include <string>
#include <vector>

using std::string;
using std::vector;

void DirectedGenerateBalancedParentheses(int, int, const string&,
                                         vector<string>*);

// @include
vector<string> GenerateBalancedParentheses(int num_pairs) {
    vector<string> result;
    DirectedGenerateBalancedParentheses(num_pairs, num_pairs, "", &result);
    return result;
}

void DirectedGenerateBalancedParentheses(int num_left_parens_needed,
                                         int num_right_parens_needed,
                                         const string& valid_prefix,
                                         vector<string>* result) {
    if (!num_left_parens_needed && !num_right_parens_needed) {
        result->emplace_back(valid_prefix);
        return;
    }

    if (num_left_parens_needed > 0) {  // Able to insert '('.
        DirectedGenerateBalancedParentheses(num_left_parens_needed - 1,
                                            num_right_parens_needed,
                                            valid_prefix + '(', result);
    }

    if (num_left_parens_needed < num_right_parens_needed) {
        // Able to insert ')'.
        DirectedGenerateBalancedParentheses(num_left_parens_needed,
                                            num_right_parens_needed - 1,
                                            valid_prefix + ')', result);
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_GENERATE_PARENTHESES_H
