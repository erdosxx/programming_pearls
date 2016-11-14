#ifndef ALGORITHM_ANALYSIS_PREFIX_SEARCH_H
#define ALGORITHM_ANALYSIS_PREFIX_SEARCH_H
// 12.1.4 Variant Search a sorted array for first occurrence of k

#include <vector>
#include <string>

using std::vector;
using std::string;

int search_prefix(const vector<string>& A, const string& prefix) {
    int result = -1;

    if (A.size() == 0) {
        return result;
    }

    int left = 0;
    int right = A.size() -1;
    int middle;

    while (left <= right) {
        middle = left + (right-left)/2;
        if (A[middle] < prefix) {
            left = middle +1;
        } else if (A[middle] == prefix) {
            return middle;
        } else { // A[middle] > prefix
            // when size of string is lower than substring size
            // just copy in existing.
            string substr = A[middle].substr(0, prefix.size());
            if (substr == prefix) {
                return middle;
            }
            right = middle -1;
        }
    }
    return result;
}

#endif //ALGORITHM_ANALYSIS_PREFIX_SEARCH_H
