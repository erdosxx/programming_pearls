#ifndef ALGORITHM_ANALYSIS_PARITY3_H
#define ALGORITHM_ANALYSIS_PARITY3_H

#include <array>

using std::array;

namespace Parity3 {

    // array<T,N> : N elements of type T
    array<short, 1 << 16> BuildTable() {
        array<short, 1 << 16> result;

        for (int i = 0; i < (1 << 16); ++i) {
            result[i] = Parity1::Parity(i);
        }
        return result;
    }

    static array<short, 1 << 16> precomputed_parity = BuildTable();

// @include
    short Parity(unsigned long x) {
        const int kWordSize = 16;
        const int kBitMask = 0xFFFF;
        return precomputed_parity[x >> (3 * kWordSize)] ^
               precomputed_parity[(x >> (2 * kWordSize)) & kBitMask] ^
               precomputed_parity[(x >> kWordSize) & kBitMask] ^
               precomputed_parity[x & kBitMask];
    }
// @exclude

}  // namespace Parity3

#endif //ALGORITHM_ANALYSIS_PARITY3_H
