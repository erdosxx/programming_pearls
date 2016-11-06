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

// @include
    bool CanFormPalindrome(const string& s) {
        // unordered_map VS map:
        // see http://stackoverflow.com/questions/13799593/how-to-choose-between-map-and-unordered-map
        unordered_map<char, int> char_frequencies;
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
// @exclude

    string RandString(int len) {
        string ret;
        default_random_engine gen((random_device())());
        while (len--) {
            uniform_int_distribution<int> dis('a', 'z');
            ret += dis(gen);
        }
        return ret;
    }
}  // namespace CanStringBeAPalindromeHash

#endif //ALGORITHM_ANALYSIS_CAN_STRING_BE_PALINDROME_HASH_H
