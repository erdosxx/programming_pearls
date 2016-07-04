#ifndef ALGORITHM_ANALYSIS_PARTITION_ARRAY_H
#define ALGORITHM_ANALYSIS_PARTITION_ARRAY_H

#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::hash;
using std::max;
using std::swap;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

// @include
struct Person {
    int age;
    string name;
};

void GroupByAge(vector<Person>* person_array) {
    unordered_map<int, int> age_to_count;
    for (const Person& p : *person_array) {
        ++age_to_count[p.age];
    }

    unordered_map<int, int> age_to_offset;
    int offset = 0;
    for (const auto& p : age_to_count) {
        age_to_offset[p.first] = offset;
        offset += p.second;
    }

    // Algorithm is very complex.
    // See Aladin Note page: 13 Friday May
    while (age_to_offset.size()) {
        auto from = age_to_offset.begin();
        auto to = age_to_offset.find((*person_array)[from->second].age);

        swap((*person_array)[from->second], (*person_array)[to->second]);
        // Use age_to_count to see when we are finished with a particular age.
        --age_to_count[to->first];
        if (age_to_count[to->first] > 0) {
            ++to->second;
        } else {
            age_to_offset.erase(to);
        }
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_PARTITION_ARRAY_H
