#ifndef ALGORITHM_ANALYSIS_ROTATE_ARRAY_PERMUTATION_H
#define ALGORITHM_ANALYSIS_ROTATE_ARRAY_PERMUTATION_H
// 25.6 Rotate an array

#include <algorithm>
#include <vector>

#include "GCD2.h"

using std::swap;
using std::vector;

namespace rotate_array1 {

    void ApplyCyclicPermutation(int, int, int, vector<int>*);
    void ApplyCyclicPermutation2(int, int, int, vector<int>*);

    void RotateArray(int rotate_amount, vector<int>* A_ptr) {
        rotate_amount %= A_ptr->size();
        int num_cycles = GCD2::GCD(A_ptr->size(), rotate_amount);
        int cycle_length = A_ptr->size() / num_cycles;

        for (int c = 0; c < num_cycles; ++c) {
            ApplyCyclicPermutation2(rotate_amount, c, cycle_length, A_ptr);
        }
    }

    void ApplyCyclicPermutation(int rotate_amount, int offset, int cycle_length,
                                vector<int>* A_ptr) {
        vector<int>& A = *A_ptr;
        int temp = A[offset];

        for (int i = 1; i < cycle_length; ++i) {
            swap(A[(offset + i * rotate_amount) % A.size()], temp);
        }
        A[offset] = temp;
    }

    // more simplified version
    // A  B  C  D  swap(A, B)
    // B  A  C  D  swap(B, C)
    // C  A  B  D  swap(C, D)
    // D  A  B  C
     void ApplyCyclicPermutation2(int rotate_amount, int offset, int cycle_length,
                                vector<int>* A_ptr) {
        vector<int>& A = *A_ptr;

        for (int i = 1; i < cycle_length; ++i) {
            swap(A[(offset + i * rotate_amount) % A.size()], A[offset]);
        }
    }
}

#endif //ALGORITHM_ANALYSIS_ROTATE_ARRAY_PERMUTATION_H
