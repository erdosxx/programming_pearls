#ifndef ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_EMPLOYEE_H
#define ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_EMPLOYEE_H
// Amazon
/*
[LCA employee]

The employee hierarchy at Initech is represented in the form of a tree. 
The CEO of the company stands at the top of the hierarchy. 
Employees can have other employees reporting to them.
An employee with at least one reportee is called a manager. 
All the employees eventually report up to the CEO.

Write an algorithm to find the closest common manager for the two given employees 
i.e. the manager who is farthest from the CEO, but to whom both the employees report. 
One of the two given employee may be the closest common manager if one reports to the other.

Input
    The input to the function/method consists of three arguments 
    - ceo, representing the CEO of the company;
    employee1, representing the first employee and 
    employee2, representing the second employee.

Output
    Return the closest common manager of the two given employees.

Constraints
    The names of all employees are unique.
    Excluding CEO, all the employees have exactly one reporting manager.

Help description
class Employee {
private:
    int id;
    std::string name;
    std::vector reports;

public:
    Employee(int id, std::string name);
    int getId();
    std::string getName();
}

Function snippet
    Employee* closestCommonManager(Employee* ceo, Employee* employee1, Employee* employee2)
{
}
*/


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
