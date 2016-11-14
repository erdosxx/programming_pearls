#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_LOCAL_MINIMUM_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_LOCAL_MINIMUM_H
// 12.1.2 Variant Search a sorted array for first occurrence of k

#include <vector>
#include <stdexcept>

using std::vector;
using std::invalid_argument;

int get_derivative(const vector<int> A, size_t i) {
    if (i >= A.size()-1)
        throw invalid_argument("get_derivative: invalid argument!");

    return A[i+1] - A[i];
};

bool check_local_minimum(const vector<int> A, size_t i) {
    if (i >= A.size()-1 || i <= 0)
        throw invalid_argument("check_local_minimum: invalid argument!");

    return A[i-1] >= A[i] && A[i] <= A[i+1];
};

int search_local_minimum(const vector<int>& A) {
    if (A.size() < 3) { // not enough elements
        return -1;
    } else if (A.size() == 3) { // according to problem condition index 1 must be local min.
        return 1;
    }

    int low = 1;
    int high = A.size() -2;
    int middle;
    int result = -1;

    while ( low <= high ) {
        middle = low + (high - low)/2;
        int derivative_high = get_derivative(A, middle);
        int derivative_low = get_derivative(A, middle-1);

        if (derivative_high > 0 && derivative_low >0) {
            high = middle - 1;
        } else if(derivative_high > 0 && derivative_low <= 0) {
            result = middle;
            return result;
        } else if (derivative_high < 0) {
            low = middle + 1;
        } else {
            bool is_local_min = check_local_minimum(A, middle);
            if(is_local_min) {
                result = middle;
                return result;
            } else {
                high = middle - 1;
            }
        }
    }

    return result;
}

#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_LOCAL_MINIMUM_H
