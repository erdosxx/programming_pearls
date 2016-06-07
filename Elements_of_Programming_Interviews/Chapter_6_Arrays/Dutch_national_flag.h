#ifndef ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_H
#define ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_H

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

// @include
namespace DutchFlag {
//typedef enum { RED, WHITE, BLUE } Color;
    using Color = enum {
        RED, WHITE, BLUE
    };

    void DutchFlagPartition(int pivot_index, vector<Color> *A_ptr) {
        //vector<Color> &A = *A_ptr;
        // alias A does not necessary. Instead of A[i], we can use A_ptr->at(i)
        Color pivot = A_ptr->at(pivot_index);
        /**
         * Keep the following invariants during partitioning:
         * bottom group: A[0 : smaller - 1].
         * middle group: A[smaller : equal - 1].
         * unclassified group: A[equal : larger - 1].
         * top group: A[larger : A.size() - 1].
         */
        int smaller = 0, equal = 0, larger = A_ptr->size();
        // Keep iterating as long as there is an unclassified element.
        while (equal < larger) {
            // A[equal] is the incoming unclassified element.
            if (A_ptr->at(equal) < pivot) {
                swap(A_ptr->at(smaller++), A_ptr->at(equal++));
            } else if (A_ptr->at(equal) == pivot) {
                ++equal;
            } else {  // A[equal] > pivot.
                swap(A_ptr->at(equal), A_ptr->at(--larger));
            }
        }
    }

    vector<Color> RandVector(int len) {
        default_random_engine gen((random_device()) ());
        vector<Color> ret;
        while (len--) {
            uniform_int_distribution<int> dis(0, 2);
            ret.push_back(static_cast<Color>(dis(gen)));
        }
        return ret;
    }
}
#endif //ALGORITHM_ANALYSIS_DUTCH_NATIONAL_FLAG_H
