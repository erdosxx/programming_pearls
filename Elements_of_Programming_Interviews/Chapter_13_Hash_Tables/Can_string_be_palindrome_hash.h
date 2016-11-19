#ifndef ALGORITHM_ANALYSIS_CAN_STRING_BE_PALINDROME_HASH_H
#define ALGORITHM_ANALYSIS_CAN_STRING_BE_PALINDROME_HASH_H
// 13.1 Test for palindromic permutations

#include <string>
#include <unordered_map>
#include <utility>

using std::string;
using std::unordered_map;
using std::pair;

namespace CanStringBeAPalindromeHash {

    bool CanFormPalindrome(const string& s) {
        unordered_map<char, size_t> char_frequencies;
        // Compute the frequency of each char in s.
        for (char c : s) {
            ++char_frequencies[c];
        }

        // A string can be permuted as a palindrome if and only if the number of
        // chars whose frequencies is odd is at most 1.
        int odd_frequency_count = 0;
        //for (const pair<char, int>& p : char_frequencies) {
        for (const auto& p : char_frequencies) {
            if ((p.second % 2) && ++odd_frequency_count > 1) {
                return false;
            }
        }
        return true;
    }

}  // namespace CanStringBeAPalindromeHash

#endif //ALGORITHM_ANALYSIS_CAN_STRING_BE_PALINDROME_HASH_H
