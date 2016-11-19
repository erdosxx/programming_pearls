#ifndef ALGORITHM_ANALYSIS_SWAPBITS_H
#define ALGORITHM_ANALYSIS_SWAPBITS_H
// 5.2 Swap bits

long SwapBits(long x, int i, int j) {
    // Extract the i-th and j-th bits, and see if they differ.
    if (((x >> i) & 1) != ((x >> j) & 1)) {
        // i-th and j-th bits differ. We will swap them by flipping their values.
        // Select the bits to flip with bitMask. Since x^1 = 0 when x = 1 and 1
        // when x = 0, we can perform the flip XOR.
        unsigned long bit_mask = (1L << i) | (1L << j);
        x ^= bit_mask;
    }
    return x;
}

#endif //ALGORITHM_ANALYSIS_SWAPBITS_H
