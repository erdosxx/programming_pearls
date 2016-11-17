#ifndef ALGORITHM_ANALYSIS_RPN_H
#define ALGORITHM_ANALYSIS_RPN_H
// 9.2 Evaluate RPN expressions

#include <sstream>
#include <stack>
#include <string>

using std::stack;
using std::string;
using std::stringstream;
using std::stoi;

// @include
int Eval(const string& RPN_expression) {
    stack<int> intermediate_results;
    stringstream ss(RPN_expression);
    string token;
    const char kDelimiter = ',';

    while (getline(ss, token, kDelimiter)) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int y = intermediate_results.top();
            intermediate_results.pop();
            int x = intermediate_results.top();
            intermediate_results.pop();

            //switch (token[0]) {
            switch (token.front()) {
                case '+':
                    intermediate_results.emplace(x + y);
                    break;
                case '-':
                    intermediate_results.emplace(x - y);
                    break;
                case '*':
                    intermediate_results.emplace(x * y);
                    break;
                case '/':
                    intermediate_results.emplace(x / y);
                    break;
            }
        } else {  // token is a number.
            intermediate_results.emplace(stoi(token));
        }
    }
    return intermediate_results.top();
}
// @exclude

#endif //ALGORITHM_ANALYSIS_RPN_H
