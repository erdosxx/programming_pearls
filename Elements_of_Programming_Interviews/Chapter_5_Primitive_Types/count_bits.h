#ifndef ALGORITHM_ANALYSIS_COUNT_BITS_H
#define ALGORITHM_ANALYSIS_COUNT_BITS_H
// 5. Primitive Types boot camp

// @include
short CountBits(unsigned int x) {
    short num_bits = 0;

    while (x) {
        num_bits += x & 1;
        x >>= 1;
    }

    return num_bits;
}
// @exclude

short CountBits_imp(unsigned int x) {
    short num_bits = 0;
    // x & (x-1)
    // 1011  1
    // 1010  2
    // 1000  3
    // 0000
    while (x) {
        // x = x & (x-1);
        x &= (x-1);
        num_bits++;
    }

    return num_bits;
}
#endif //ALGORITHM_ANALYSIS_COUNT_BITS_H
