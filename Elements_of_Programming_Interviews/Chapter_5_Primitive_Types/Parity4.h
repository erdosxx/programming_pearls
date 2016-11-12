#ifndef ALGORITHM_ANALYSIS_PARITY4_H
#define ALGORITHM_ANALYSIS_PARITY4_H
// 5.1 Computing the parity of a word

namespace Parity4 {

// @include
    short Parity(unsigned long x) {
        x ^= x >> 32;
        x ^= x >> 16;
        x ^= x >> 8;
        x ^= x >> 4;
        x ^= x >> 2;
        x ^= x >> 1;
        return x & 0x1; // mask upto 16 bit (last 1 bit).
    }
// @exclude

}  // namespace Parity4

#endif //ALGORITHM_ANALYSIS_PARITY4_H
