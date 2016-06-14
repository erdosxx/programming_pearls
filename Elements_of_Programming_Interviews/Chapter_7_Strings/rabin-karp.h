#ifndef ALGORITHM_ANALYSIS_RABIN_KARP_H
#define ALGORITHM_ANALYSIS_RABIN_KARP_H

#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::random_device;
using std::string;
using std::uniform_int_distribution;
using std::vector;

namespace rabin_karp {
// @include
// Returns the index of the first character of the substring if found, -1
// otherwise.
    int RabinKarp(const string &t, const string &s) {
        if (s.size() > t.size()) {
            return -1;  // s is not a substring of t.
        }

        const int kBase = 26;
        int t_hash = 0;
        int s_hash = 0;  // Hash codes for the substring of t and s.
        int power_s = 1;  // kBase^|s|.

        for (int i = 0; i < s.size(); ++i) {
            power_s = i ? power_s * kBase : 1;
            t_hash = t_hash * kBase + t[i];
            s_hash = s_hash * kBase + s[i];
        }

        for (int i = s.size(); i < t.size(); ++i) {
            // Checks the two substrings are actually equal or not, to protect
            // against hash collision.
            if (t_hash == s_hash && !t.compare(i - s.size(), s.size(), s)) {
                return i - s.size();  // Found a match.
            }

            // Uses rolling hash to compute the new hash code.
            t_hash -= t[i - s.size()] * power_s;
            t_hash = t_hash * kBase + t[i];
        }

        // Tries to match s and t[t.size() - s.size() : t.size() - 1].
        if (t_hash == s_hash && t.compare(t.size() - s.size(), s.size(), s) == 0) {
            return t.size() - s.size();
        }
        return -1;  // s is not a substring of t.
    }
// @exclude

    int CheckAnswer(const string &t, const string &s) {
        for (int i = 0; i + s.size() - 1 < t.size(); ++i) {
            bool find = true;
            for (int j = 0; j < s.size(); ++j) {
                if (t[i + j] != s[j]) {
                    find = false;
                    break;
                }
            }
            if (find == true) {
                return i;
            }
        }
        return -1;  // No matching.
    }

    string RandString(int len) {
        default_random_engine gen((random_device()) ());
        string ret;
        while (len--) {
            uniform_int_distribution<char> dis('a', 'z');
            ret += dis(gen);
        }
        return ret;
    }
}

#endif //ALGORITHM_ANALYSIS_RABIN_KARP_H
