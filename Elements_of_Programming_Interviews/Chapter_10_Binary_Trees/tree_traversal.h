#ifndef ALGORITHM_ANALYSIS_TREE_TRAVERSAL_H
#define ALGORITHM_ANALYSIS_TREE_TRAVERSAL_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "Binary_tree_prototype.h"

using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;
using btree::BinaryTreeNode;
using std::vector;
using std::string;

// @include
void TreeTraversal(const unique_ptr<BinaryTreeNode<int>>& root) {
    if (root) {
        // Preorder: Processes the root before the traversals of left and right
        // children.
        cout << "Preorder: " << root->data << endl;

        TreeTraversal(root->left);
        // Inorder: Processes the root after the traversal of left child and
        // before the traversal of right child.
        cout << "Inorder: " << root->data << endl;
        TreeTraversal(root->right);
        // Postorder: Processes the root after the traversals of left and right
        // children.
        cout << "Postorder: " << root->data << endl;
    }
}
// @exclude

void TreeTraversal_preorder(const unique_ptr<BinaryTreeNode<int>>& root, vector<int>* traversal_ptr) {
    if (root) {
        //cout << "Preorder: " << root->data << endl;
        traversal_ptr->emplace_back(root->data);

        TreeTraversal_preorder(root->left, traversal_ptr);
        TreeTraversal_preorder(root->right, traversal_ptr);
    }
}

void TreeTraversal_inorder(const unique_ptr<BinaryTreeNode<int>>& root, vector<int>* traversal_ptr) {
    if (root) {
        TreeTraversal_inorder(root->left, traversal_ptr);

        //cout << "Inorder: " << root->data << endl;
        traversal_ptr->emplace_back(root->data);

        TreeTraversal_inorder(root->right, traversal_ptr);
    }
}

void TreeTraversal_postorder(const unique_ptr<BinaryTreeNode<int>>& root, vector<int>* traversal_ptr) {
    if (root) {
        TreeTraversal_postorder(root->left, traversal_ptr);
        TreeTraversal_postorder(root->right, traversal_ptr);

        //cout << "Postorder: " << root->data << endl;
        traversal_ptr->emplace_back(root->data);
    }
}

vector<int> generate_traversal(const unique_ptr<BinaryTreeNode<int>>& root, const string & traversal_type) {
    vector<int> traversal;
    if (traversal_type == "preorder") {
        TreeTraversal_preorder(root, &traversal);
    } else if (traversal_type == "postorder") {
        TreeTraversal_postorder(root, &traversal);
    } else { // inorder traversal
        TreeTraversal_inorder(root, &traversal);
    }

    return traversal;
}

#endif //ALGORITHM_ANALYSIS_TREE_TRAVERSAL_H
