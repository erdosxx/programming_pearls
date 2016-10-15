#ifndef ALGORITHM_ANALYSIS_SEARCH_MAJORITY_H
#define ALGORITHM_ANALYSIS_SEARCH_MAJORITY_H

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

using std::istringstream;
using std::string;
using std::vector;

// @include
string MajoritySearch(istringstream* input_stream) {
    string candidate, iter;
    int candidate_count = 0;

    while (*input_stream >> iter) {
        if (candidate_count == 0) {
            candidate = iter;
            candidate_count = 1;
        } else if (candidate == iter) {
            ++candidate_count;
        } else {
            --candidate_count;
        }
    }

    return candidate;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_SEARCH_MAJORITY_H
