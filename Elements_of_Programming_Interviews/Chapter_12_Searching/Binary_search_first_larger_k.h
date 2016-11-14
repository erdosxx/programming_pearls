#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_FIRST_LARGER_K_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_FIRST_LARGER_K_H
// 12.1.1 Variant Search a sorted array for first occurrence of k

int SearchFirstOfLargerK(const vector<int>& A, int k) {
    int low = 0;
    int high = A.size() -1;
    int middle;
    int result = -1;

    while (low <= high) {
        middle = low + (high - low)/2;

        if (A[middle] <= k) {
            low = middle +1;
        } else {
            result = middle;
            high = middle -1;
        }
    }

    return result;
}


#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_FIRST_LARGER_K_H
