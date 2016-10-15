#ifndef ALGORITHM_ANALYSIS_ROTATE_ARRAY_H
#define ALGORITHM_ANALYSIS_ROTATE_ARRAY_H

#include <algorithm>
#include <vector>

using std::vector;

namespace rotate_array2 {

// @include
    void RotateArray(int i, vector<int>* A) {
        i %= A->size();
        reverse(A->begin(), A->end());
        reverse(A->begin(), A->begin() + i);
        reverse(A->begin() + i, A->end());
    }
// @exclude

}  // rotate_array2

#endif //ALGORITHM_ANALYSIS_ROTATE_ARRAY_H
