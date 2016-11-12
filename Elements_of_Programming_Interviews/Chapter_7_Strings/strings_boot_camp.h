#ifndef ALGORITHM_ANALYSIS_STRINGS_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_STRINGS_BOOT_CAMP_H
// 7. Strings Boot Camp

#include <string>

using std::string;

bool IsPalindromic(const string& s) {
    for (int i = 0, j = s.size() - 1; i < j ; i++, j--) {
        if (s[i] != s[j]) {
            return false;
        }
    }
    return true;
}

#endif //ALGORITHM_ANALYSIS_STRINGS_BOOT_CAMP_H
