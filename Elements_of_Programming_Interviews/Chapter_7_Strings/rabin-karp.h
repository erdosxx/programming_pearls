#ifndef ALGORITHM_ANALYSIS_RABIN_KARP_H
#define ALGORITHM_ANALYSIS_RABIN_KARP_H

#include <string>
#include <vector>

using std::string;
using std::vector;

int get_next_hash(int* prev_hash_ptr, const int& pattern_size, const int& kBase, const int& power_n, const string* text_ptr, const int& n);

//  power_n = (kBase)^(pattern.size() -1)
//  ex) pattern = abc, power_n = kBase^2
int get_power_n(int kBase, int pattern_size) {
    int power_n = 1;

    for (int i = 0; i < pattern_size-1; ++i) {
        power_n *= kBase;
    }
    return power_n;
}

int get_hash(const string* str_ptr, int start_pos, int size, int kBase) {
    const string& str = *str_ptr;
    int hash_val = 0;

    for (int i = start_pos; i < start_pos + size; ++i) {
        hash_val = hash_val * kBase + str[i];
    }
    return  hash_val;
}

//  p = KBase
//  h1  |--------|
//      C0 C1 C2 C3 C4
//  h2     |---------|
//  h1 = C0*p^3 + C1*p^2 + C2*p + C3
//  h2 = C1*p^3 + C2*p^2 + C3*p + C4
//  h2 = p * (h1 - C0* p^3) + C4
//                      |-- power_n

int RabinKarp(const string& text, const string& pattern) {
    if (pattern.size() > text.size()) {
        return -1;  // s is not a substring of t.
    }

    const int kBase = 26;
    int power_n = get_power_n(kBase, pattern.size());
    int pattern_hash = get_hash(&pattern, 0, pattern.size(), kBase);

    int text_hash;
    // Example
    // pattern = 123
    // text = 0123456789
    // i= 0 ~ 7
    for (int i = 0; i <= text.size() - pattern.size(); ++i) {
        text_hash = get_next_hash(&text_hash, pattern.size(), kBase, power_n, &text, i);

        string text_substr = text.substr(i, pattern.size());

        if(text_hash == pattern_hash && text_substr == pattern) {
            return i;
        }
    }

    return -1;  // s is not a substring of t.
}

// power_n = (kBase)^(pattern.size() -1)
// h_n = kBase * (h_n-1 - C_n-1 * powern_n) + C_n+pattern_size-1
int get_next_hash(int* prev_hash_ptr, const int& pattern_size, const int& kBase,
                  const int& power_n, const string* text_ptr, const int& n) {
    int& pre_hash = *prev_hash_ptr;
    const string& text = *text_ptr;

    if (n == 0) {
        pre_hash = get_hash(&text, 0, pattern_size, kBase);
        return pre_hash;
    }

    pre_hash = kBase * (pre_hash - text[n-1] * power_n) + text[n + pattern_size -1];

    return pre_hash;
}

#endif //ALGORITHM_ANALYSIS_RABIN_KARP_H
