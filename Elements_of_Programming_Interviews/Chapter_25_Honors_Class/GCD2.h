#ifndef ALGORITHM_ANALYSIS_GCD2_H
#define ALGORITHM_ANALYSIS_GCD2_H

namespace GCD2 {

// @include
    long long GCD(long long x, long long y) { return y == 0 ? x : GCD(y, x % y); }
// @exclude

}  // namespace GCD2

#endif //ALGORITHM_ANALYSIS_GCD2_H
