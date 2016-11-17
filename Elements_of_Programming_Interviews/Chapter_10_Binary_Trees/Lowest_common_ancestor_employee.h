#ifndef ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_EMPLOYEE_H
#define ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_EMPLOYEE_H
// Amazon

#include <string>
#include <vector>

using std::string;
using std::vector;

class Employee {
private:
    int _id;
    string _name;
    vector<Employee*> _reporters;

public:
    int getId() const {
        return _id;
    }

    string getName() const {
        return _name;
    };

    Employee(int id, string name, vector<Employee*> reports) {
        _id = id;
        _name = name;
        _reporters = reports;
    }

    vector<Employee*> getReporters() const {
        return _reporters;
    }
};

struct state {
    int num_of_targets = 0;
    Employee* LCA;
};

state closestCommonManager2_helper(Employee* root_ptr, const Employee*& employee1_ptr, const Employee*& employee2_ptr) {
    if (root_ptr == nullptr) {
        return {0, nullptr};
    }

    int num_reporters = root_ptr->getReporters().size();
    vector<state> results(num_reporters);

    for (int i = 0; i < num_reporters; ++i) {
        results[i] = closestCommonManager2_helper(root_ptr->getReporters()[i], employee1_ptr, employee2_ptr);
        if (results[i].num_of_targets == 2) {
            return results[i];
        }
    }

    int num_targets = 0;
    for (int i= 0; i < num_reporters; ++i) {
        num_targets += results[i].num_of_targets;
    }

    num_targets = num_targets + (root_ptr == employee1_ptr) + (root_ptr == employee2_ptr);

    return {num_targets, num_targets == 2 ? root_ptr : nullptr};
}

Employee* closestCommonManager2(Employee* ceo, const Employee*& employee1_ptr, const Employee*& employee2_ptr) {
    return closestCommonManager2_helper(ceo, employee1_ptr, employee2_ptr).LCA;
}

#endif //ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_EMPLOYEE_H
