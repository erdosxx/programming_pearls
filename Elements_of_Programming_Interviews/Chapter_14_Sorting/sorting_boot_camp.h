#ifndef ALGORITHM_ANALYSIS_SORTING_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_SORTING_BOOT_CAMP_H
// 14. Sorting Boot Camp

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Student {
    bool operator < (const Student& that) const {
        return name < that.name;
    }

    string name;
    double grade_point_average;
};

// sort by descending order

auto gpa_comp = [](const Student& a, const Student& b) -> bool {
             return a.grade_point_average >= b.grade_point_average;
         };

void SortByGPA(vector<Student>* students) {
    sort(students->begin(), students->end(), gpa_comp);
}

void SortByName(vector<Student>* students) {
    // Rely on the operator< defined in Student.
    sort(students->begin(), students->end());
}

#endif //ALGORITHM_ANALYSIS_SORTING_BOOT_CAMP_H
