#ifndef ALGORITHM_ANALYSIS_ANAGRAMS_H
#define ALGORITHM_ANALYSIS_ANAGRAMS_H
// 13. hash boot camp

#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

// @include
vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
    unordered_map<string, vector<string>> sorted_string_to_anagrams;

    for (const string& s : dictionary) {
        // Sorts the string, uses it as a key, and then appends
        // the original string as another value into hash table.
        string sorted_str(s);
        sort(sorted_str.begin(), sorted_str.end());
        sorted_string_to_anagrams[sorted_str].emplace_back(s);
    }

    vector<vector<string>> anagram_groups;
    for (const auto& p : sorted_string_to_anagrams) {
        if (p.second.size() >= 2) {  // Found anagrams.
            anagram_groups.emplace_back(p.second);
        }
    }
    return anagram_groups;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_ANAGRAMS_H
