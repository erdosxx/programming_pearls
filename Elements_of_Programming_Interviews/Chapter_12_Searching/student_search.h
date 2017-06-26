#ifndef ALGORITHM_ANALYSIS_STUDENT_SEARCH_H
#define ALGORITHM_ANALYSIS_STUDENT_SEARCH_H
// 12 Searching boot camp

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

using std::binary_search;
using std::function;
using std::sort;
using std::string;
using std::vector;

struct Student {
    string name;
    double grade_point_average;
};

// Sorted by descending GPA, with ties broken on name.
const static function<bool(const Student&, const Student&)> CompGPA = [](
        const Student& a, const Student& b) {
    if (a.grade_point_average != b.grade_point_average) {
        return a.grade_point_average > b.grade_point_average;
    }
    return a.name < b.name;
};

auto compGPA_lamda = [](const Student& a, const Student& b) -> bool {
    if (a.grade_point_average != b.grade_point_average) {
        return a.grade_point_average > b.grade_point_average;
    }
    return a.name < b.name;
};

bool comp_student_f (const Student& a, const Student& b) {
    if (a.grade_point_average != b.grade_point_average) {
        return a.grade_point_average > b.grade_point_average;
    }
    return a.name < b.name;
}

decltype(&comp_student_f) comp_student_f_ptr = &comp_student_f;

bool SearchStudent(
        const vector<Student>& students, const Student& target,
        const function<bool(const Student&, const Student&)>& comp_GPA) {
    return binary_search(students.begin(), students.end(), target, comp_GPA);
}

bool SearchStudent2(
        const vector<Student>& students, const Student& target,
        decltype(compGPA_lamda)) {
    return binary_search(students.begin(), students.end(), target, compGPA_lamda);
}

struct Student_with_compare {
    string name;
    int grade_point_average;

    bool operator<(const Student_with_compare& that) const {
        if (grade_point_average != that.grade_point_average) {
            return grade_point_average > that.grade_point_average;
        }
        return name < that.name;
    }

    // To use "find" we need to define == operator.
    bool operator==(const Student_with_compare& that) const {
        return grade_point_average == that.grade_point_average &&
                name == that.name;
    }
};

struct compare_dec_gpa_inc_name {
    bool operator()(const Student_with_compare& a, const Student_with_compare& b) const {
        if(a.grade_point_average != b.grade_point_average) {
            return a.grade_point_average > b.grade_point_average;
        }
        return a.name < b.name;
    }
};

#endif //ALGORITHM_ANALYSIS_STUDENT_SEARCH_H
