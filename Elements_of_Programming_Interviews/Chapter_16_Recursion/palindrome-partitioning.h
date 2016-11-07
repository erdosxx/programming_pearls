#ifndef ALGORITHM_ANALYSIS_PALINDROME_PARTITIONING_H
#define ALGORITHM_ANALYSIS_PALINDROME_PARTITIONING_H
// 16.7 Generate palindromic decompositions

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::string;
using std::vector;

bool IsPalindrome(const string&);
void DirectedPalindromePartitioning(const string&, int, vector<string>*,
                                    vector<vector<string>>*);

// @include
vector<vector<string>> PalindromePartitioning(const string& input) {
    vector<vector<string>> result;
    DirectedPalindromePartitioning(input, 0, new vector<string>, &result);
    return result;
}

void DirectedPalindromePartitioning(const string& input, int offset,
                                    vector<string>* partial_partition,
                                    vector<vector<string>>* result) {
    if (offset == input.size()) {
        result->emplace_back(*partial_partition);
        return;
    }

    for (int i = offset + 1; i <= input.size(); ++i) {
        // string substr (size_t pos = 0, size_t len = npos) const;
        string prefix = input.substr(offset, i - offset);
        if (IsPalindrome(prefix)) {
            partial_partition->emplace_back(prefix);
            DirectedPalindromePartitioning(input, i, partial_partition, result);
            partial_partition->pop_back();
        }
    }
}

bool IsPalindrome(const string& prefix) {
    for (int i = 0, j = prefix.size() - 1; i < j; ++i, --j) {
        if (prefix[i] != prefix[j]) {
            return false;
        }
    }
    return true;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_PALINDROME_PARTITIONING_H
