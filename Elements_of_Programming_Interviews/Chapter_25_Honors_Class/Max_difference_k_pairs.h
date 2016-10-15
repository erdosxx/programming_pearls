#ifndef ALGORITHM_ANALYSIS_MAX_DIFFERENCE_K_PAIRS_H
#define ALGORITHM_ANALYSIS_MAX_DIFFERENCE_K_PAIRS_H

#include <algorithm>
#include <limits>
#include <vector>

using std::max;
using std::numeric_limits;
using std::vector;

// @include
double MaxKPairsProfits(const vector<double> &A, int k) {
  vector<double> k_sum(2 * k, numeric_limits<double>::lowest());

  for (int i = 0; i < A.size(); ++i) {
    vector<double> pre_k_sum(k_sum);

    for (int j = 0, sign = -1; j < k_sum.size() && j <= i; ++j, sign *= -1) {
      double diff = sign * A[i] + (j == 0 ? 0 : pre_k_sum[j - 1]);

      k_sum[j] = max(diff, pre_k_sum[j]);
    }
  }

  return k_sum.back();  // Returns the last selling profits as the answer.
}
// @exclude

#endif //ALGORITHM_ANALYSIS_MAX_DIFFERENCE_K_PAIRS_H
