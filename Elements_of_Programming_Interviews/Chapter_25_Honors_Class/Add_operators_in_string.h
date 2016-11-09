#ifndef ALGORITHM_ANALYSIS_ADD_OPERATORS_IN_STRING_H
#define ALGORITHM_ANALYSIS_ADD_OPERATORS_IN_STRING_H
// 25.27 Synthesize an expression

#include <stack>
#include <string>
#include <vector>

using std::stack;
using std::string;
using std::vector;

bool DirectedExpressionSynthesis(const vector<int>&, int, int, int,
                                 vector<int>*, vector<char>*);
int RemainingInt(const vector<int>&, int);
int Evaluate(const vector<int>&, const vector<char>&);

// @include
bool ExpressionSynthesis(const vector<int>& digits, int target) {
    vector<char> operators;
    vector<int> operands;
    return DirectedExpressionSynthesis(digits, target, 0, 0, &operands,
                                       &operators);
}

bool DirectedExpressionSynthesis(const vector<int>& digits, int target,
                                 int current_term, int offset,
                                 vector<int>* operands,
                                 vector<char>* operators) {
    current_term = current_term * 10 + digits[offset];

    if (offset == digits.size() - 1) {
        operands->emplace_back(current_term);

        if (Evaluate(*operands, *operators) == target) {  // Found a match.
            // @exclude
            /*
            auto operand_it = operands->cbegin();
            cout << *operand_it++;
            for (char oper : *operators) {
                cout << ' ' << oper << ' ' << *operand_it++;
            }
            cout << " = " << target << endl;
            */
            // @include
            return true;
        }
        operands->pop_back();
        return false;
    }

    // No operator.
    if (DirectedExpressionSynthesis(digits, target, current_term, offset + 1,
                                    operands, operators)) {
        return true;
    }

    // Tries multiplication operator '*'.
    operands->emplace_back(current_term);
    operators->emplace_back('*');
    if (DirectedExpressionSynthesis(digits, target, 0, offset + 1, operands,
                                    operators)) {
        return true;
    }
    operands->pop_back();
    operators->pop_back();

    // Tries addition operator '+'.
    operands->emplace_back(current_term);
    // First check feasibility of plus operator.
    if (target - Evaluate(*operands, *operators) <=
        RemainingInt(digits, offset + 1)) {
        operators->emplace_back('+');
        if (DirectedExpressionSynthesis(digits, target, 0, offset + 1, operands,
                                        operators)) {
            return true;
        }
        operators->pop_back();
    }
    operands->pop_back();
    return false;
}

// Calculates the int represented by digits[idx : digits.size() - 1].
int RemainingInt(const vector<int>& digits, int idx) {
    int val = 0;
    for (int i = idx; i < digits.size(); ++i) {
        val = val * 10 + digits[i];
    }
    return val;
}

int Evaluate(const vector<int>& operands, const vector<char>& operators) {
    stack<int> intermediate_operands;
    int operand_idx = 0;
    intermediate_operands.push(operands[operand_idx++]);

    // Evaluates '*' first.
    for (char oper : operators) {
        if (oper == '*') {
            int product = intermediate_operands.top() * operands[operand_idx++];
            intermediate_operands.pop();
            intermediate_operands.push(product);
        } else {  // oper == '+'.
            intermediate_operands.push(operands[operand_idx++]);
        }
    }

    // Evaluates '+' second.
    int sum = 0;
    while (!intermediate_operands.empty()) {
        sum += intermediate_operands.top();
        intermediate_operands.pop();
    }
    return sum;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_ADD_OPERATORS_IN_STRING_H
