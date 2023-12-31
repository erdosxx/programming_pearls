#ifndef ALGORITHM_ANALYSIS_PHONE_MNEMONIC_H
#define ALGORITHM_ANALYSIS_PHONE_MNEMONIC_H
// 7.7 Compute all mnemonics for a phone number

#include <array>
#include <string>
#include <vector>

using std::array;
using std::string;
using std::vector;

    // The mapping from digit to corresponding characters.
    const array<string, 10> kMapping = {
            {"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"}};

    // DFS search for generating phone mnemonic.
    void PhoneMnemonicHelper(const string& phone_number, int digit,
                             string* partial_mnemonic,
                             vector<string>* mnemonics) {
        if (digit == phone_number.size()) {
            // All digits are processed, so add partial_mnemonic to mnemonics.
            // (We add a copy since subsequent calls modify partial_mnemonic.)
            mnemonics->emplace_back(*partial_mnemonic);
        } else {
            // Try all possible characters for this digit.
            for (char c : kMapping[phone_number[digit] - '0']) {
                (*partial_mnemonic)[digit] = c;
                PhoneMnemonicHelper(phone_number, digit + 1, partial_mnemonic,
                                    mnemonics);
            }
        }
    }

    vector<string> PhoneMnemonic(const string& phone_number) {
        // string (size_t n, char c) : Fills the string with n consecutive copies of character c.
        string partial_mnemonic(phone_number.size(), 0);
        vector<string> mnemonics;
        PhoneMnemonicHelper(phone_number, 0, &partial_mnemonic, &mnemonics);
        return mnemonics;
    }

#endif //ALGORITHM_ANALYSIS_PHONE_MNEMONIC_H
