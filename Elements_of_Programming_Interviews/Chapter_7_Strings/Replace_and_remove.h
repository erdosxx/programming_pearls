#ifndef ALGORITHM_ANALYSIS_REPLACE_AND_REMOVE_H
#define ALGORITHM_ANALYSIS_REPLACE_AND_REMOVE_H
// 7.4 Replace and remove

#include <string>

using std::string;

namespace r_n_r {
// @include
    int ReplaceAndRemove(int size, char s[]) {
        // Forward iteration: remove "b"s and count the number of "a"s.
        int write_idx = 0;
        int a_count = 0;

        for (int i = 0; i < size; ++i) {
            if (s[i] != 'b') {
                s[write_idx++] = s[i];
            }

            if (s[i] == 'a') {
                ++a_count;
            }
        }

        // Backward iteration: replace "a"s with "dd"s starting from the end.
        int cur_idx = write_idx - 1;
        write_idx = cur_idx + a_count;
        int final_size = write_idx + 1;

        while (cur_idx >= 0) {
            if (s[cur_idx] == 'a') {
                s[write_idx--] = 'd';
                s[write_idx--] = 'd';
            } else {
                s[write_idx--] = s[cur_idx];
            }
            --cur_idx;
        }
        return final_size;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_REPLACE_AND_REMOVE_H
