#ifndef ALGORITHM_ANALYSIS_MULTIPLYSHIFTADD_H
#define ALGORITHM_ANALYSIS_MULTIPLYSHIFTADD_H
// 5.5 Compute x * y without arithmetical operators

unsigned Add(unsigned a, unsigned b);

// @include
unsigned Multiply(unsigned x, unsigned y) {
    unsigned sum = 0;
    while (x) {
        // Examines each bit of x.
        if (x & 1) {
            sum = Add(sum, y);
        }
        x >>= 1, y <<= 1;
    }
    return sum;
}

unsigned Add(unsigned a, unsigned b) {
    unsigned sum = 0, carryin = 0, k = 1, temp_a = a, temp_b = b;
    // Multiply for every digit.
    while (temp_a || temp_b) {
        unsigned ak = a & k, bk = b & k;
        unsigned carryout = (ak & bk) | (ak & carryin) | (bk & carryin);
        sum |= (ak ^ bk ^ carryin);
        carryin = carryout << 1, k <<= 1, temp_a >>= 1, temp_b >>= 1;
    }
    return sum | carryin;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_MULTIPLYSHIFTADD_H
