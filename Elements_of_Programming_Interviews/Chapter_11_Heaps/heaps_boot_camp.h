#ifndef ALGORITHM_ANALYSIS_HEAPS_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_HEAPS_BOOT_CAMP_H

#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <functional>

using std::string;
using std::vector;
using std::istringstream;
using std::priority_queue;
using std::function;

vector<string> TopK(int k, istringstream* stream) {
    priority_queue<string, vector<string>, function<bool(string, string)>>
            min_heap([](const string& a, const string& b) -> bool {
                return a.size() >= b.size();
            });

    string next_string;
    while (*stream >> next_string) {
        min_heap.emplace(next_string);

        if(min_heap.size() > k) {
            // Remove the shortest string. Note that the comparision function above
            // will order the strings by length.
            min_heap.pop();
        }
    }

    vector<string> result;
    while(!min_heap.empty()) {
        result.emplace_back(min_heap.top());
        min_heap.pop();
    }

    return result;
}

#endif //ALGORITHM_ANALYSIS_HEAPS_BOOT_CAMP_H
