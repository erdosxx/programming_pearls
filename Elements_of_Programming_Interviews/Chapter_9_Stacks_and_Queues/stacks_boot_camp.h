#ifndef ALGORITHM_ANALYSIS_STACKS_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_STACKS_BOOT_CAMP_H

#include <stack>
#include <iostream>
#include <string>
#include "Linked_list_prototype.h"

using std::stack;
using std::cout;
using std::endl;
using std::string;

string PrintLinkedListInReverse(shared_ptr<ListNode<int>>* head_ptr) {
    shared_ptr<ListNode<int>>& head = *head_ptr;

    stack<int> nodes;

    while (head) {
        nodes.push(head->data);
        head = head->next;
    }

    string result="";
    while (!nodes.empty()) {
        // cout << nodes.top() << endl;
        result += '0' + nodes.top();
        result += "<-";
        nodes.pop();
    }

    return result;
}

#endif //ALGORITHM_ANALYSIS_STACKS_BOOT_CAMP_H
