#ifndef PROGRAMMING_PEARLS_PERMUTE_THE_ELEMENTS_OF_AN_ARRAY_6_9_H
#define PROGRAMMING_PEARLS_PERMUTE_THE_ELEMENTS_OF_AN_ARRAY_6_9_H

using std::vector;
using std::string;

namespace permute_the_elements {
    vector<string> apply(const vector<int> *p_permutation, vector<string> *p_array) {
        if (p_permutation->size() == 0)
            return {};
        else
            return *p_array;
    }
}

#endif //PROGRAMMING_PEARLS_PERMUTE_THE_ELEMENTS_OF_AN_ARRAY_6_9_H
