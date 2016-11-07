#ifndef ALGORITHM_ANALYSIS_FIND_MISSING_AND_DUPLICATE_XOR_H
#define ALGORITHM_ANALYSIS_FIND_MISSING_AND_DUPLICATE_XOR_H
// 12.10 Find the duplicate and missing elements

#include <vector>

// See also:
// http://stackoverflow.com/questions/3492302/easy-interview-question-got-harder-given-numbers-1-100-find-the-missing-numbe/3492664#3492664

using std::vector;

// @include
struct DuplicateAndMissing {
    int duplicate, missing;
};

DuplicateAndMissing FindDuplicateMissing(const vector<int>& A) {
    // Compute the XOR of all numbers from 0 to |A| - 1 and all entries in A.
    int miss_XOR_dup = 0;
    for (int i = 0; i < A.size(); ++i) {
        miss_XOR_dup ^= i ^ A[i];
    }

    // We need to find a bit that's set to 1 in miss_XOR_dup. Such a bit
    // must exist if there is a single missing number and a single duplicated
    // number in A.
    //
    // The bit-fiddling assignment below sets all of bits in differ_bit to 0
    // except for the least significant bit in miss_XOR_dup that's 1.
    int differ_bit = miss_XOR_dup & (~(miss_XOR_dup - 1));
    int miss_or_dup = 0;
    for (int i = 0; i < A.size(); ++i) {
        // Focus on entries and numbers in which the differ_bit-th bit is 1.
        if (i & differ_bit) {
            miss_or_dup ^= i;
        }
        if (A[i] & differ_bit) {
            miss_or_dup ^= A[i];
        }
    }

    // miss_or_dup is either the missing value or the duplicated entry.
    for (int A_i : A) {
        if (A_i == miss_or_dup) {  // miss_or_dup is the duplicate.
            return {miss_or_dup, miss_or_dup ^ miss_XOR_dup};
        }
    }
    // miss_or_dup is the missing value.
    return {miss_or_dup ^ miss_XOR_dup, miss_or_dup};
}
// @exclude


#endif //ALGORITHM_ANALYSIS_FIND_MISSING_AND_DUPLICATE_XOR_H
