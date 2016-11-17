#ifndef ALGORITHM_ANALYSIS_POLISH_NOTATION_H
#define ALGORITHM_ANALYSIS_POLISH_NOTATION_H
// 9.2.1 Variant Evaluate RPN expressions

#include <string>
#include <stack>
#include <sstream>

using std::stringstream;

using std::stack;
using std::string;
using std::stoi;
using std::istringstream;
using std::to_string;

bool isNumber(string str) {
   double d;
   istringstream is(str);
   is >> d;
   return !is.fail() && is.eof();
}

int get_op_result(stack<string> *intermediate_results, const int &token_num);
int cal_operator(const int &op_result, const int &top_token_num, const string &op);

int eval_polish_notation(const string& PN_expression) {
   stack<string> intermediate_results;

   stringstream ss(PN_expression);
   string token;
   const char delimiter = ',';

   while (getline(ss, token, delimiter)) {
      if (token == "+" || token == "-" || token == "*" || token == "/") {
         intermediate_results.emplace(token);
      } else { // for number input
         int token_num = stoi(token);
         string top_token = intermediate_results.top();

         if (! isNumber(top_token)) {
            intermediate_results.emplace(token);
         } else { // top_token is number
            int op_result = get_op_result(&intermediate_results, token_num);

            intermediate_results.emplace(to_string(op_result));
         }
      }
   }
   return stoi(intermediate_results.top());
}

int get_op_result(stack<string>* intermediate_results_ptr, const int &token_num) {
   stack<string>& intermediate_results = *intermediate_results_ptr;

   int op_result = token_num;
   string top_token;

   while (! intermediate_results.empty() && isNumber(top_token = intermediate_results.top())) {
      int top_token_num = stoi(top_token);
      intermediate_results.pop();

      string op = intermediate_results.top();
      intermediate_results.pop();

      op_result = cal_operator(op_result, top_token_num, op);
   }
   return op_result;
}

int cal_operator(const int& token_num, const int& top_token_num, const string& op) {
   int op_result;

   switch (op.front()) {
         case '+':
            op_result = top_token_num + token_num;
              break;
         case '-':
            op_result = top_token_num - token_num;
              break;
         case '*':
            op_result = top_token_num * token_num;
              break;
         case '/':
            op_result = top_token_num / token_num;
              break;
      }
   return op_result;
}

#endif //ALGORITHM_ANALYSIS_POLISH_NOTATION_H
