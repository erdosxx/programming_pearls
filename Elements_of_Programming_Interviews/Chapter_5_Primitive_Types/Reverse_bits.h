#ifndef ALGORITHM_ANALYSIS_REVERSE_BITS_H
#define ALGORITHM_ANALYSIS_REVERSE_BITS_H
// 5.3 Reverse bits

#include <vector>

#include "swapbits.h"

using std::vector;

long ReverseX(long x, int n) {
    for (int i = 0, j = n; i < j; ++i, --j) {
        x = SwapBits(x, i, j);
    }
    return x;
}

vector<long> precomputed_reverse;

void CreatePrecomputedTable() {
    for (int i = 0; i < (1 << 16); ++i) {
        precomputed_reverse.emplace_back(ReverseX(i, 15));
    }
}

// (abcd)^R = d^R c^R b^R a^R
long ReverseBits(long x) {
    const int kWordSize = 16;
    const int kBitMask = 0xFFFF;
    return precomputed_reverse[x & kBitMask] << (3 * kWordSize) |
           precomputed_reverse[(x >> kWordSize) & kBitMask] << (2 * kWordSize) |
           precomputed_reverse[(x >> (2 * kWordSize)) & kBitMask] << kWordSize |
           precomputed_reverse[(x >> (3 * kWordSize)) & kBitMask];
}

#endif //ALGORITHM_ANALYSIS_REVERSE_BITS_H
