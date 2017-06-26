#ifndef ALGORITHM_ANALYSIS_PARITY1_H
#define ALGORITHM_ANALYSIS_PARITY1_H
// 5.1 Computing the parity of a word

// See Hacker's Delight page 96.
namespace Parity1 {

    short Parity(unsigned long x) {
        short result = 0;

        while (x) {
            result ^= (x & 1);
            x >>= 1;
        }
        return result;
    }

}

#endif //ALGORITHM_ANALYSIS_PARITY1_H
