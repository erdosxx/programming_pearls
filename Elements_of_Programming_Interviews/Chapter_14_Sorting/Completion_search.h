#ifndef ALGORITHM_ANALYSIS_COMPLETION_SEARCH_H
#define ALGORITHM_ANALYSIS_COMPLETION_SEARCH_H
// 14.10 Compute a salary threshold

#include <algorithm>
#include <vector>

using std::vector;

// @include
double FindSalaryCap(double target_payroll, vector<double> current_salaries) {
    sort(current_salaries.begin(), current_salaries.end());
    double unadjusted_salary_sum = 0.0;
    double adjusted_salary_sum = 0.0;

    for (int i = 0; i < current_salaries.size(); ++i) {
        adjusted_salary_sum =
                current_salaries[i] * (current_salaries.size() - i);

        if (unadjusted_salary_sum + adjusted_salary_sum >= target_payroll) {
            return (target_payroll - unadjusted_salary_sum) /
                   (current_salaries.size() - i);
        }
        unadjusted_salary_sum += current_salaries[i];
    }
    // No solution, since target_payroll > existing payroll.
    return -1.0;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_COMPLETION_SEARCH_H
