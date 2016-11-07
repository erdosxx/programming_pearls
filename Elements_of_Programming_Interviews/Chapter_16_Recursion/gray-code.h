#ifndef ALGORITHM_ANALYSIS_GRAY_CODE_H
#define ALGORITHM_ANALYSIS_GRAY_CODE_H
// 16.10 Compute a Gray code

#include <algorithm>
#include <string>
#include <vector>

using std::string;
using std::vector;

// @include
vector<int> GrayCode(int num_bits) {
    if (num_bits == 0) {
        return {0};
    }
    if (num_bits == 1) {
        return {0, 1};
    }

    // These implicitly begin with 0 at bit-index (num_bits - 1).
    auto gray_code_num_bits_minus_1 = GrayCode(num_bits - 1);
    // Now, add a 1 at bit-index (num_bits - 1) to all entries in
    // grayCodeNumBitsMinus1.
    int leading_bit_one = 1 << (num_bits - 1);
    vector<int> reflection;
    // Process in reverse order to achieve reflection of
    // gray_code_num_bits_minus_1.
    for (int i = gray_code_num_bits_minus_1.size() - 1; i >= 0; --i) {
        reflection.emplace_back(leading_bit_one | gray_code_num_bits_minus_1[i]);
    }
    vector<int> result = gray_code_num_bits_minus_1;
    result.insert(result.end(), reflection.begin(), reflection.end());
    return result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_GRAY_CODE_H
