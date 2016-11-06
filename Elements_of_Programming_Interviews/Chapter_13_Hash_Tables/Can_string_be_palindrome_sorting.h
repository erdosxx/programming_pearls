#ifndef ALGORITHM_ANALYSIS_CAN_STRING_BE_PALINDROME_SORTING_H
#define ALGORITHM_ANALYSIS_CAN_STRING_BE_PALINDROME_SORTING_H
// 13.1 Test for palindromic permutations

#include <algorithm>
#include <string>

using std::string;

namespace CanStringBeAPalindromeSorting {

// @exclude
    // change original code parameter type:  string* s -> string& s
    bool CanFormPalindrome(string& s) {
        sort(s.begin(), s.end());
        int odd_count = 0, num_curr_char = 1;

        for (int i = 1; i < s.size() && odd_count <= 1; ++i) {
            if (s[i] != s[i - 1]) {
                if (num_curr_char % 2) {
                    ++odd_count;
                }
                num_curr_char = 1;
            } else {
                ++num_curr_char;
            }
        }
        if (num_curr_char % 2) { // for last (*s)[s->size() -1]
            ++odd_count;
        }

        // A string can be permuted as a palindrome if the number of odd time
        // chars <= 1.
        return odd_count <= 1;
    }
// @exclude

}  // namespace CanStringBeAPalindromeSorting

#endif //ALGORITHM_ANALYSIS_CAN_STRING_BE_PALINDROME_SORTING_H
