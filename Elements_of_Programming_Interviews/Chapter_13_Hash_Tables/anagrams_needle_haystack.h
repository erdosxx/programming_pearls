#ifndef ALGORITHM_ANALYSIS_ANAGRAMS_NEEDLE_HAYSTACK_H
#define ALGORITHM_ANALYSIS_ANAGRAMS_NEEDLE_HAYSTACK_H
// Source: Amazon test
// input:  haystack: abdaghbaabcdij
//                   ^       ^
//         needle:   bcda
// output: [0, 8]

#include <vector>

using std::vector;

size_t string_hash(const string& str) {
    size_t result = str[0];

    for (int i = 1; i < str.size(); ++i) {
        result ^= str[i];
    }

    return result;
}

// for main idia, see EPI 7.13 page 98.
size_t rolling_hash(const char& new_char, const char& prev_char, const size_t& prev_hash) {

    // prev_char ^ prev_char = 0
    // 0 ^ new_char = new_char
    return prev_hash ^ prev_char ^ new_char;
}

string insertion_sort_string(const string& str) {
    string result = str;

    for (int i = 1; i < str.size(); ++i) {
        char tmp = result[i];
        int j;
        for (j = i; j >0 && result[j-1] > tmp; --j) {
            result[j] = result[j-1];
        }
        result[j] =tmp;
    }

    return result;
}

// using sort in <algorithm>
string sort_string(const string& str) {
    string result = str;
    sort(result.begin(), result.end());

    return result;
}

bool anagram_compare(const string& a, const string& b) {
    if (a.size() != b.size()) {
        return false;
    }

    // we could not possible to use sort in <algorithm>.
    //if (sort_string(a) == sort_string(b)) {

    // for speed up comparision, we use hash comparision before sorting.
    if (string_hash(a) == string_hash(b) &&
            insertion_sort_string(a) == insertion_sort_string(b)) {
        return true;
    }

    return false;
}

bool anagram_compare(const string& a, const string& sorted_b, const size_t& hash_b) {
    if (a.size() != sorted_b.size()) {
        return false;
    }

    // we could not possible to use sort in <algorithm>.
    //if (sort_string(a) == sort_string(b)) {

    // for speed up comparision, we use hash comparision before sorting.
    if (string_hash(a) == hash_b &&
            insertion_sort_string(a) == sorted_b) {
        return true;
    }

    return false;
}

// for using rolling hash
bool anagram_compare(const string& a, const char& removed_char, size_t* prev_hash_ptr, const string& sorted_b, const size_t& hash_b) {
    if (a.size() != sorted_b.size()) {
        return false;
    }

    *prev_hash_ptr = rolling_hash(a[a.size()-1], removed_char, *prev_hash_ptr);

    if (*prev_hash_ptr == hash_b &&
        insertion_sort_string(a) == sorted_b) {
        return true;
    }

    return false;
}

vector<int> getAnagramIndices(const string& haystack, const string& needle) {
    vector<int> result = {};

    if (haystack.size() < needle.size()) {
        return result;
    }

    string sorted_needle = insertion_sort_string(needle);
    size_t hash_needle = string_hash(needle);


    // Ex) needle: 01 => 2
    //     haystack: 0123456 => 7
    for (int i = 0; i <= haystack.size() - needle.size(); ++i) {
        string sbstr = haystack.substr(i, needle.size());

        //if (anagram_compare(sbstr, needle)) {
        // for preventing repeatedly compute sort and hash for needle.
        if (anagram_compare(sbstr, sorted_needle, hash_needle)) {
            result.emplace_back(i);
        }
    }

    return result;
}

// rollinghash version.
vector<int> getAnagramIndices2(const string& haystack, const string& needle) {
    vector<int> result = {};

    if (haystack.size() < needle.size()) {
        return result;
    }

    string sorted_needle = insertion_sort_string(needle);
    size_t hash_needle = string_hash(needle);


    // for case i = 0
    //bool anagram_compare(const string& a, const string& sorted_b, const size_t& hash_b) {
    if (anagram_compare(haystack.substr(0, needle.size()), sorted_needle, hash_needle)) {
        result.emplace_back(0);
    }

    size_t hash_haystack_substr = string_hash(haystack.substr(0, needle.size()));

    // for case i = 1 ~ use rolling hash to speed up.
    // Ex) needle: 01 => 2
    //     haystack: 0123456 => 7
    for (int i = 1; i <= haystack.size() - needle.size(); ++i) {
        string sbstr = haystack.substr(i, needle.size());
        char removed_char = haystack[i-1];

        if (anagram_compare(sbstr, removed_char, &hash_haystack_substr, sorted_needle, hash_needle)) {
            result.emplace_back(i);
        }
    }

    return result;
}
#endif //ALGORITHM_ANALYSIS_ANAGRAMS_NEEDLE_HAYSTACK_H
