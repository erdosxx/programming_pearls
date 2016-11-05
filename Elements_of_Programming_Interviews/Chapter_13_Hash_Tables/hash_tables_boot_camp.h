#ifndef ALGORITHM_ANALYSIS_HASH_TABLES_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_HASH_TABLES_BOOT_CAMP_H

#include <string>

using std::string;

int StringHash(const string& str, int modulus) {
    const int kMult = 997;  // prime number
    int val = 0;
    for (char c : str) {
        val = (kMult * val + c) % modulus;
    }
    return val;
}

#endif //ALGORITHM_ANALYSIS_HASH_TABLES_BOOT_CAMP_H
