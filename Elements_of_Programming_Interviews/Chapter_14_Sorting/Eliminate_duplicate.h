#ifndef ALGORITHM_ANALYSIS_ELIMINATE_DUPLICATE_H
#define ALGORITHM_ANALYSIS_ELIMINATE_DUPLICATE_H

#include <algorithm>
#include <string>
#include <vector>

using std::string;
using std::vector;

// @include
struct Name {
    bool operator==(const Name& that) const {
        return first_name == that.first_name;
    }

    bool operator<(const Name& that) const {
        if (first_name != that.first_name) {
            return first_name < that.first_name;
        }
        return last_name < that.last_name;
    }

    string first_name, last_name;
};

void EliminateDuplicate(vector<Name>* A) {
    sort(A->begin(), A->end());  // Makes identical elements become neighbors.
    // unique() removes adjacent duplicates and returns an iterator to the
    // element the follows the last element not removed. The effect of erase()
    // is to restrict A to the distinct elements.
    // see: http://www.cplusplus.com/reference/algorithm/unique/
    A->erase(unique(A->begin(), A->end()), A->end());
}
// @exclude


#endif //ALGORITHM_ANALYSIS_ELIMINATE_DUPLICATE_H
