#ifndef ALGORITHM_ANALYSIS_FIND_K_LARGEST_BST_H
#define ALGORITHM_ANALYSIS_FIND_K_LARGEST_BST_H

#include <memory>
#include <vector>

#include "BST_prototype.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;

void FindKLargestInBSTHelper(const unique_ptr<BSTNode<int>>&, int,
                             vector<int>*);

// @include
vector<int> FindKLargestInBST(const unique_ptr<BSTNode<int>>& tree, int k) {
    vector<int> k_largest_elements;
    FindKLargestInBSTHelper(tree, k, &k_largest_elements);
    return k_largest_elements;
}

void FindKLargestInBSTHelper(const unique_ptr<BSTNode<int>>& tree, int k,
                             vector<int>* k_largest_elements) {
    // Perform reverse inorder traversal.
    if (tree && k_largest_elements->size() < k) {
        FindKLargestInBSTHelper(tree->right, k, k_largest_elements);
        if (k_largest_elements->size() < k) {
            k_largest_elements->emplace_back(tree->data);
            FindKLargestInBSTHelper(tree->left, k, k_largest_elements);
        }
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_FIND_K_LARGEST_BST_H
