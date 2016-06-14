#ifndef ALGORITHM_ANALYSIS_REPLACE_AND_REMOVE_H
#define ALGORITHM_ANALYSIS_REPLACE_AND_REMOVE_H

#include <cassert>
#include <iostream>
#include <random>
#include <string>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;

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
        write_idx = write_idx + a_count - 1;
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

    string RandString(int len) {
        default_random_engine gen((random_device()) ());
        string ret;
        while (len--) {
            uniform_int_distribution<char> dis('a', 'd');
            ret += dis(gen);
        }
        return ret;
    }

    bool CheckAns(const string &s, const string &ans) {
        string temp;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'a') {
                temp += 'd', temp += 'd';
            } else if (s[i] != 'b') {
                temp += s[i];
            }
        }
        return ans.compare(temp) == 0;
    }
}

#endif //ALGORITHM_ANALYSIS_REPLACE_AND_REMOVE_H
