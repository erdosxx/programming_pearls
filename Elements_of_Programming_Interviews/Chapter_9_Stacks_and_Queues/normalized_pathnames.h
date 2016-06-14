#ifndef ALGORITHM_ANALYSIS_NORMALIZED_PATHNAMES_H
#define ALGORITHM_ANALYSIS_NORMALIZED_PATHNAMES_H

#include <algorithm>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

using std::exception;
using std::invalid_argument;
using std::stringstream;
using std::string;
using std::vector;

// @include
string ShortestEquivalentPath(const string& path) {
    if (path.empty()) {
        throw invalid_argument("Empty string is not a valid path.");
    }

    vector<string> path_names;  // Uses vector as a stack.
    // Special case: starts with "/", which is an absolute path.
    if (path.front() == '/') {
        path_names.emplace_back("/");
    }

    stringstream ss(path);
    string token;
    while (getline(ss, token, '/')) {
        if (token == "..") {
            if (path_names.empty() || path_names.back() == "..") {
                path_names.emplace_back(token);
            } else {
                if (path_names.back() == "/") {
                    throw invalid_argument("Path error");
                }
                path_names.pop_back();
            }
        } else if (token != "." && token != "") {  // Must be a name.
            path_names.emplace_back(token);
        }
    }

    string result;
    if (!path_names.empty()) {
        result = path_names.front();
        for (int i = 1; i < path_names.size(); ++i) {
            if (i == 1 && result == "/") {  // Avoid starting "//".
                result += path_names[i];
            } else {
                result += "/" + path_names[i];
            }
        }
    }
    return result;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_NORMALIZED_PATHNAMES_H
