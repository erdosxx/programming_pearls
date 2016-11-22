#ifndef ALGORITHM_ANALYSIS_PHONE_MNEMONIC_ITERATIVE_H
#define ALGORITHM_ANALYSIS_PHONE_MNEMONIC_ITERATIVE_H
// 7.7.1 Variant Compute all mnemonics for a phone number

#include <vector>
#include <stack>
#include <array>

using std::vector;
using std::stack;
using std::array;

vector<string> PhoneMnemonic_iterative(const string& phone_number) {
    const array<string, 10> kMapping =
            {{"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"}};

    vector<string> mnemonics;
    stack<string> str_stack;

    const size_t num_size = phone_number.size();

    string mne = kMapping[phone_number[0] - '0'];

    for (int i = mne.size()-1; i >= 0; --i) {
        str_stack.emplace(mne.substr(i,1));
    }

    while (! str_stack.empty()) {
        while (!str_stack.empty() && str_stack.top().size() == num_size) {
            mnemonics.emplace_back(str_stack.top());
            str_stack.pop();
        }

        if (! str_stack.empty()) {
            string n_str = str_stack.top();
            str_stack.pop();
            mne = kMapping[phone_number[n_str.size()] - '0'];

            for (int i = mne.size() - 1; i >= 0; --i) {
                str_stack.emplace(n_str + mne.substr(i, 1));
            }
        }
    }

    return mnemonics;
}

#endif //ALGORITHM_ANALYSIS_PHONE_MNEMONIC_ITERATIVE_H
