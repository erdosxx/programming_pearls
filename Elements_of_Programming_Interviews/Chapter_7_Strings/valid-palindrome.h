#ifndef ALGORITHM_ANALYSIS_VALID_PALINDROME_H
#define ALGORITHM_ANALYSIS_VALID_PALINDROME_H
// 7.5 Test palindromicity

#include <string>

using std::string;

bool IsPalindrome(const string& s) {
    // i moves forward, and j moves backward.
    int i = 0;
    int j = s.size() - 1;

    while (i < j) {
        // i and j both skip non-alphanumeric characters.
        // isalnum: Check if character is alphanumeric
        while (!isalnum(s[i]) && i < j) {
            ++i;
        }
        while (!isalnum(s[j]) && i < j) {
            --j;
        }
        if (tolower(s[i]) != tolower(s[j])) {
            return false;
        }
        ++i, --j;
    }
    return true;
}

#endif //ALGORITHM_ANALYSIS_VALID_PALINDROME_H
