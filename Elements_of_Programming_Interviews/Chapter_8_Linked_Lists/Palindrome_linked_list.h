#ifndef ALGORITHM_ANALYSIS_PALINDROME_LINKED_LIST_H
#define ALGORITHM_ANALYSIS_PALINDROME_LINKED_LIST_H
// 8.11 Test whether a singly linked list is palindromic

#include <memory>

#include "Linked_list_prototype.h"
#include "Reverse_linked_list_iterative.h"

using std::make_shared;
using std::shared_ptr;

// @include
bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
  if (L == nullptr) {
    return true;
  }

  // Finds the second half of L.
  auto slow = L;
  auto fast = L;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  // Compares the first half and the reversed second half lists.
  auto first_half_iter = L;
  auto second_half_iter = ReverseLinkedList(slow);

  while (second_half_iter && first_half_iter) {
    if (second_half_iter->data != first_half_iter->data) {
      return false;
    }
    second_half_iter = second_half_iter->next;
    first_half_iter = first_half_iter->next;
  }
  return true;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_PALINDROME_LINKED_LIST_H
