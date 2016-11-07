#ifndef ALGORITHM_ANALYSIS_PARITY2_H
#define ALGORITHM_ANALYSIS_PARITY2_H
// 5.1 Computing the parity of a word

namespace Parity2 {

// @include
    short Parity(unsigned long x) {
        short result = 0;
        while (x) {
            result ^= 1;
            x &= (x - 1);  // Drops the lowest set bit of x.
        }
        return result;
    }
// @exclude

}  // namespace Parity2

#endif //ALGORITHM_ANALYSIS_PARITY2_H
