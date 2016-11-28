#ifndef ALGORITHM_ANALYSIS_RUN_LENGTH_COMPRESSION_GOOGLE_H
#define ALGORITHM_ANALYSIS_RUN_LENGTH_COMPRESSION_GOOGLE_H
// 7.12.1 Variant Implement run-length-encoding

#include <string>
#include <stack>
#include <stdexcept>

using std::string;
using std::isdigit;
using std::stack;
using std::invalid_argument;

// advance idx to non digit char.
int get_count(const string& str, int* idx_ptr) {
    int& idx = *idx_ptr;

    if (idx >= str.size()) {
        return 0;
    }

    int count = 0;
    for (int i= idx; isdigit(str[i]) && i < str.size(); ++i) {
        count = count * 10 + str[i] - '0';
        idx = i;
    }

    return count;
}

int get_right_matching_braket_idx (const string& str, int idx) {
    if (str[idx] != '[' || idx >= str.size()) {
        throw invalid_argument("No left bracket!");
    }

    stack<char> bracket_stack;
    bracket_stack.emplace(str[idx++]);

    while (! bracket_stack.empty()) {
        if (str[idx] == '[') {
            bracket_stack.emplace(str[idx]);
        } else if (str[idx] == ']') {
            if (bracket_stack.top() != '[') {
                throw invalid_argument("Not matching bracket!");
            }
            bracket_stack.pop();
        }
        idx++;
    }
    return idx - 1;
}

string get_pattern_str(const string& str, int* idx_ptr) {
    int& idx = *idx_ptr;

    int left_bracket_idx = idx;
    int right_bracket_idx = get_right_matching_braket_idx(str, idx);

    idx = right_bracket_idx; // set index to ].

    return str.substr(left_bracket_idx+1, right_bracket_idx - left_bracket_idx -1);
}

string decoding_google(const string& rle) {
    string result;
    string pattern_str;

    for (int i = 0; i < rle.size(); ++i) {
        if (isalpha(rle[i])) {
            result.push_back(rle[i]);
        } else if (isdigit(rle[i])) {
            int count = get_count(rle, &i);
            ++i;
            pattern_str = get_pattern_str(rle, &i);

            if (pattern_str.find('[') != string::npos) {
                pattern_str = decoding_google(pattern_str);
            }

            while (count-- > 0) {
                result += pattern_str;
            }
        }
    }

    return result;
}


#endif //ALGORITHM_ANALYSIS_RUN_LENGTH_COMPRESSION_GOOGLE_H
