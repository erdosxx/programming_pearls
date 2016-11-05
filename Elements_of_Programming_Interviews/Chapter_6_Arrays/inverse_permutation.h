#ifndef ALGORITHM_ANALYSIS_INVERSE_PERMUTATION_H
#define ALGORITHM_ANALYSIS_INVERSE_PERMUTATION_H

#include <vector>
#include <algorithm>


bool isTagged(const int & val) {
    return val < 0 ? true : false;
}

// for supporting index starting 0 and 1.
void Tagging(vector<int>* perm_ptr, const size_t index, int new_val) {
    vector<int>& perm = *perm_ptr;
    perm[index] = new_val - perm.size();
}

int readVal(vector<int>* perm_ptr, const size_t & index) {
    vector<int>& perm = *perm_ptr;

    if(isTagged(perm[index])) {
        return perm[index] + perm.size();
    }
    return perm[index];
}

// 0 1 2 3 4 5           0 1 2 3 4 5
// 5 1 0 4 3 2    -->    2 1 5 4 3 0
void inverse_permutation(vector<int>* perm_ptr, bool starting_from_1) {
    vector<int>& perm = *perm_ptr;

    // convert array to 0 based
    if (starting_from_1) {
        for_each(perm.begin(), perm.end(), [&](int& x){x--;});
    }

    for (size_t prev = 0; prev < perm.size(); prev++) {
        // prev -> curr
        int curr = readVal(perm_ptr, prev);

        while (!isTagged(perm[curr])) {
            int tmp = perm[curr];
            // curr -> prev
            Tagging(perm_ptr, curr, prev);
            prev = curr;
            curr = tmp;
        }
    }

    // remove tagging.
    for_each(perm.begin(),perm.end(), [&](int& x){x += perm.size();});

    // restore array to 1 based.
    if (starting_from_1) {
        for_each(perm.begin(), perm.end(), [&](int& x){x++;});
    }
}

#endif //ALGORITHM_ANALYSIS_INVERSE_PERMUTATION_H
