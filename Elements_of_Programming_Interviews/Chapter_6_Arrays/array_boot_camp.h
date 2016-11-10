#ifndef ALGORITHM_ANALYSIS_ARRAY_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_ARRAY_BOOT_CAMP_H
// 6. Arrays Boot Camp

#include <vector>

using std::vector;
using std::swap;

bool is_odd(int num) {
    return num % 2;
}

void even_odd_groupping(vector<int>* array_ptr) {
    vector<int>& array = *array_ptr;

    int left = 0;
    int right = array.size()-1;

    while(left < right) {
        if (is_odd(array[left])) {
            swap(array[left], array[right--]);
        } else { // for even
            left++;
        }
    }
}

#endif //ALGORITHM_ANALYSIS_ARRAY_BOOT_CAMP_H
