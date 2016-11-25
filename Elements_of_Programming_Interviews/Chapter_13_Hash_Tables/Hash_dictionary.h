#ifndef ALGORITHM_ANALYSIS_HASH_DICTIONARY_H
#define ALGORITHM_ANALYSIS_HASH_DICTIONARY_H
// 13 Hash Tables boot camp

#include <numeric>
#include <random>
#include <string>

using std::default_random_engine;
using std::random_device;
using std::string;
using std::uniform_int_distribution;

namespace str_hash {
    string RandString(int len) {
        string ret;
        random_device rd;
        default_random_engine gen(rd());
        //default_random_engine gen((random_device()) ());
        while (len--) {
            uniform_int_distribution<int> zero_or_one(0, 1);
            uniform_int_distribution<char> dis(0, 26);
            ret += (zero_or_one(gen) ? 'a' : 'A') + dis(gen);
        }
        return ret;
    }

// @include
    int StringHash(const string &str, int modulus) {
        const int kMult = 997;  // prime number
        // @exclude
        /*
        return accumulate(str.cbegin(), str.cend(), 0,
          [kMult, modulus](const int &val, const char &c) -> int {
            return (val * kMult + c) % modulus;
          });
        */
        // @include
        int val = 0;
        for (char c : str) {
            val = (val * kMult + c) % modulus;
        }
        return val;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_HASH_DICTIONARY_H
