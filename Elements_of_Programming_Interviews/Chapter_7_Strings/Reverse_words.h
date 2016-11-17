#ifndef ALGORITHM_ANALYSIS_REVERSE_WORDS_H
#define ALGORITHM_ANALYSIS_REVERSE_WORDS_H
// 7.6 Reverse all the words in a sentence

#include <algorithm>
#include <string>

using std::string;

namespace reverse_words {

    void ReverseWords(string *s) {
        // Reverses the whole string first.
        // Reverses the order of the elements in the range [first,last)
        reverse(s->begin(), s->end());

        size_t start = 0;
        size_t end;

        // find: If no matches were found, the function returns string::npos.
        // find : search from start.
        while ((end = s->find(" ", start)) != string::npos) {
            // Reverses each word in the string.
            reverse(s->begin() + start, s->begin() + end);
            start = end + 1;
        }
        // Reverses the last word.
        reverse(s->begin() + start, s->end());
    }
}

#endif //ALGORITHM_ANALYSIS_REVERSE_WORDS_H
