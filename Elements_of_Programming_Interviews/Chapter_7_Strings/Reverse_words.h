#ifndef ALGORITHM_ANALYSIS_REVERSE_WORDS_H
#define ALGORITHM_ANALYSIS_REVERSE_WORDS_H
// 7.6 Reverse all the words in a sentence

#include <algorithm>
#include <string>

using std::string;

namespace reverse_words {
    string RandString(int len) {
        default_random_engine gen((random_device()) ());
        string ret;

        while (len--) {
            uniform_int_distribution<int> dis(0, 52);
            int ch = dis(gen);

            if (ch == 52) {
                ret += ' ';
            } else if (ch < 26) {
                ret += ch + 'a';
            } else {
                ret += ch - 26 + 'A';
            }
        }
        return ret;
    }

// @include
    void ReverseWords(string *s) {
        // Reverses the whole string first.
        // Reverses the order of the elements in the range [first,last)
        reverse(s->begin(), s->end());

        size_t start = 0;
        size_t end;

        // find: If no matches were found, the function returns string::npos.
        while ((end = s->find(" ", start)) != string::npos) {
            // Reverses each word in the string.
            reverse(s->begin() + start, s->begin() + end);
            start = end + 1;
        }
        // Reverses the last word.
        reverse(s->begin() + start, s->end());
    }
// @exclude

    bool CheckAnswer(const string &ori, string *str) {
        ReverseWords(str);
        return ori.compare(*str) == 0;
    }
}

#endif //ALGORITHM_ANALYSIS_REVERSE_WORDS_H
