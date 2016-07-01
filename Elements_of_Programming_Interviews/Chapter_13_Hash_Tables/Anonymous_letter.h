#ifndef ALGORITHM_ANALYSIS_ANONYMOUS_LETTER_H
#define ALGORITHM_ANALYSIS_ANONYMOUS_LETTER_H

#include <algorithm>
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;

// @include
bool IsLetterConstructibleFromMagazine(const string &letter_text,
                                       const string &magazine_text) {
    unordered_map<char, int> char_frequency_for_letter;
    // Compute the frequencies for all chars in letter_text.
    for (char c : letter_text) {
        ++char_frequency_for_letter[c];
    }

    // Check if the characters in magazine_text can cover characters
    // in char_frequency_for_letter.
    for (char c : magazine_text) {
        //unordered_map<char,int>::iterator it = char_frequency_for_letter.find(c);
        auto it = char_frequency_for_letter.find(c);
        if (it != char_frequency_for_letter.cend()) {
            --(it->second);
            if (it->second == 0) {
                char_frequency_for_letter.erase(it);
                if (char_frequency_for_letter.empty()) {
                    // All characters for letter_text are matched.
                    break;
                }
            }
        }
    }
    // Empty char_frequency_for_letter means every char in letter_text can be
    // covered by a character in magazine_text.
    return char_frequency_for_letter.empty();
}
// @exclude

#endif //ALGORITHM_ANALYSIS_ANONYMOUS_LETTER_H
