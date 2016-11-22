#ifndef ALGORITHM_ANALYSIS_REMOVE_DUPLICATES_FROM_SORTED_ARRAY_H
#define ALGORITHM_ANALYSIS_REMOVE_DUPLICATES_FROM_SORTED_ARRAY_H
// 6.5 Delete duplicates from a sorted array

#include <vector>

using std::vector;

// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    if (A.empty()) {
        return 0;
    }

    int write_index = 1;
    for (int i = 1; i < A.size(); ++i) {
        if (A[write_index - 1] != A[i]) {
            A[write_index++] = A[i];
        }
    }
    return write_index;
}


#endif //ALGORITHM_ANALYSIS_REMOVE_DUPLICATES_FROM_SORTED_ARRAY_H
