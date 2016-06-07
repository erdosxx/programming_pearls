#ifndef ALGORITHM_ANALYSIS_CLOSEST_INT_SAME_BITS_H
#define ALGORITHM_ANALYSIS_CLOSEST_INT_SAME_BITS_H

#include <stdexcept>

using std::exception;
using std::invalid_argument;

// @include
const int kNumUnsignBits = 64;

unsigned long ClosestIntSameBitCount(unsigned long x) {
    for (int i = 0; i < kNumUnsignBits - 1; ++i) {
        if (((x >> i) & 1) != ((x >> (i + 1)) & 1)) {
            x ^= (1UL << i) | (1UL << (i + 1));  // Swaps bit-i and bit-(i + 1).
            return x;
        }
    }

    // Throw error if all bits of x are 0 or 1.
    throw invalid_argument("All bits are 0 or 1");
}
// @exclude

int CountBitsSetTo1(unsigned long x) {
    int count = 0;
    while (x) {
        x &= (x - 1);
        ++count;
    }
    return count;
}

#endif //ALGORITHM_ANALYSIS_CLOSEST_INT_SAME_BITS_H
