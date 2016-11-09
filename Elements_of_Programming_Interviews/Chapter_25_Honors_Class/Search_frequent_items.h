#ifndef ALGORITHM_ANALYSIS_SEARCH_FREQUENT_ITEMS_H
#define ALGORITHM_ANALYSIS_SEARCH_FREQUENT_ITEMS_H
// 25.37 The heavy hitter problem

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::ios;
using std::istringstream;
using std::string;
using std::unordered_map;
using std::vector;

// @include
// Finds the candidates which may occur > n / k times.
// See for more detail theory:
// http://web.stanford.edu/class/cs168/l/l2.pdf
vector<string> SearchFrequentItems(int k, istringstream* sin) {
    string buf;
    unordered_map<string, int> hash;
    int n = 0;  // Count the number of strings.

    while (*sin >> buf) {
        ++hash[buf], ++n;
        // Detecting k items in hash, at least one of them must have exactly
        // one in it. We will discard those k items by one for each.
        if (hash.size() == k) {
            auto it = hash.begin();
            while (it != hash.end()) {
                if (--(it->second) == 0) {
                    hash.erase(it++);
                } else {
                    ++it;
                }
            }
        }
    }

    // Resets hash for the following counting.
    for (auto& it : hash) {
        it.second = 0;
    }

    // Resets the stream and read it again.
    sin->clear();
    sin->seekg(0, ios::beg);
    // Counts the occurrence of each candidate word.
    while (*sin >> buf) {
        auto it = hash.find(buf);
        if (it != hash.end()) {
            ++it->second;
        }
    }

    // Selects the word which occurs > n / k times.
    vector<string> ret;
    for (const auto& it : hash) {
        if (it.second > static_cast<double>(n) / k) {
            ret.emplace_back(it.first);
        }
    }
    return ret;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SEARCH_FREQUENT_ITEMS_H
