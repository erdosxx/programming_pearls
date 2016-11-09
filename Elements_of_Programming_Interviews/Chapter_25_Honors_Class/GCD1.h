#ifndef ALGORITHM_ANALYSIS_GCD1_H
#define ALGORITHM_ANALYSIS_GCD1_H
// 25.1 Compute the greatest common divisor

namespace GCD1 {

// @include
    long long GCD(long long x, long long y) {
        if (x == y) {
            return x;
        } else if (!(x & 1) && !(y & 1)) {  // x and y are even.
            return GCD(x >> 1, y >> 1) << 1;
        } else if (!(x & 1) && y & 1) {  // x is even, and y is odd.
            return GCD(x >> 1, y);
        } else if (x & 1 && !(y & 1)) {  // x is odd, and y is even.
            return GCD(x, y >> 1);
        } else if (x > y) {  // Both x and y are odd, and x > y.
            return GCD(x - y, y);
        }
        return GCD(x, y - x);  // Both x and y are odd, and x <= y.
    }
// @exclude
    // See Weiss page 92.
    long long GCD2(long long x, long long y) {
        if (x == y) {
            return x;
        } else if (!(x & 1) && !(y & 1)) {  // x and y are even.
            return GCD2(x >> 1, y >> 1) << 1;
        } else if (!(x & 1) && y & 1) {  // x is even, and y is odd.
            return GCD2(x >> 1, y);
        } else if (x & 1 && !(y & 1)) {  // x is odd, and y is even.
            return GCD2(x, y >> 1);
        } else if (x > y) {  // Both x and y are odd, and x > y.
            // not work by overflow: return GCD2( (x + y) >> 1 , (x - y) >> 1);
            return GCD2( y + ((x - y) >> 1) , (x - y) >> 1);
        }
        // not work by overflow: return GCD2((y + x) >> 1 , (y - x) >> 1);  // Both x and y are odd, and x <= y.
        return GCD2(x + ((y - x) >> 1) , (y - x) >> 1);  // Both x and y are odd, and x <= y.
    }
}  // namespace GCD1

#endif //ALGORITHM_ANALYSIS_GCD1_H
