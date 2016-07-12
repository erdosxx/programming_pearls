#ifndef ALGORITHM_ANALYSIS_INSERTION_DELETION_BST_H
#define ALGORITHM_ANALYSIS_INSERTION_DELETION_BST_H

#include <memory>

using std::make_unique;
using std::unique_ptr;

// @include
template <typename Comparable>
class BinarySearchTree {
public:
    // @exclude
    bool Empty() const { return !root_.get(); }

    // @include
    bool Insert(const Comparable & key) {
        // Two unique_ptr compare equal (==) if their stored pointers compare equal, and not equal (!=) otherwise.
        if (root_ == nullptr) {
            root_ = make_unique<TreeNode>(TreeNode{key});
        } else {
            TreeNode *curr = root_.get();
            TreeNode *parent = nullptr;

            while (curr != nullptr) {
                parent = curr;
                if (key == curr->data) {
                    return false;  // key already present, no duplicates to be added.
                } else if (key < curr->data) {
                    curr = curr->left.get();
                } else {  // key > curr->data.
                    curr = curr->right.get();
                }
            }

            // Inserts key according to key and parent.
            if (key < parent->data) {
                parent->left.reset(new TreeNode{key});
            } else {
                parent->right.reset(new TreeNode{key});
            }
        }
        return true;
    }

    bool rInsert(const Comparable & key) {
        return rInsertHelper(key, root_);
    }

    bool Delete(const Comparable & key) {
        // Find the node with key.
        TreeNode *curr = root_.get();
        TreeNode *parent = nullptr;

        while (curr && curr->data != key) {
            parent = curr;
            curr = key < curr->data ? curr->left.get() : curr->right.get();
        }

        if (!curr) {
            // There's no node with key in this tree.
            return false;
        }

        TreeNode *key_node = curr;
        if (key_node->right) {
            // Finds the minimum of the right subtree.
            TreeNode *r_key_node = key_node->right.get();
            TreeNode *r_parent = key_node;

            while (r_key_node->left) {
                r_parent = r_key_node;
                r_key_node = r_key_node->left.get();
            }

            key_node->data = r_key_node->data;
            // Moves links to erase the node.
            if (r_parent->left.get() == r_key_node) {
                r_parent->left.reset(r_key_node->right.release());
            } else {  // r_parent->right.get() == r_key_node.
                r_parent->right.reset(r_key_node->right.release());
            }
        } else {
            // Updates root_ link if needed.
            if (root_.get() == key_node) {
                root_.reset(key_node->left.release());
            } else {
                if (parent->left.get() == key_node) {
                    parent->left.reset(key_node->left.release());
                } else {  // parent->right.get() == key_node.
                    parent->right.reset(key_node->left.release());
                }
            }
        }
        return true;
    }

    bool rDelete (const Comparable & key) {
        return rDeleteHelper (key, root_);
    }
    // @exclude
    int GetRootVal() const { return root_->data; }
    // @include

private:
    struct TreeNode {
        Comparable data;
        unique_ptr<TreeNode> left, right;
        TreeNode(Comparable key): data{key}, left{nullptr}, right{nullptr} {}
    };

    unique_ptr<TreeNode> root_ = nullptr;

    bool rInsertHelper (const Comparable & key, unique_ptr<TreeNode> & uniq_ptr) {
        bool ret_val;
        if (uniq_ptr == nullptr) {
            uniq_ptr.reset(new TreeNode{key});
            ret_val = true;
        } else if (key < uniq_ptr->data) {
            ret_val = rInsertHelper(key, uniq_ptr->left);
        } else if (key > uniq_ptr->data) {
            ret_val = rInsertHelper(key, uniq_ptr->right);
        } else {// Duplicate Do nothing.
            ret_val = false;
        }
        return ret_val;
    }

    bool rDeleteHelper (const Comparable & key, unique_ptr<TreeNode> & uniq_ptr) {
        bool ret_val;

        if (uniq_ptr == nullptr) {
            ret_val = false;
            return ret_val;
        }

        if (key < uniq_ptr->data) {
            ret_val = rDeleteHelper(key, uniq_ptr->left);
        } else if (key > uniq_ptr->data) {
            ret_val = rDeleteHelper(key, uniq_ptr->right);
        } else if (uniq_ptr->left != nullptr && uniq_ptr->right != nullptr) { // two children
            uniq_ptr->data = (*findMin(&(uniq_ptr->right)))->data;
            ret_val = rDeleteHelper(uniq_ptr->data, uniq_ptr->right);
        } else {
            uniq_ptr->left != nullptr ? uniq_ptr.reset(uniq_ptr->left.release()) : uniq_ptr.reset(uniq_ptr->right.release());
            ret_val= true;
        }
        return ret_val;
    }

    unique_ptr<TreeNode>* findMin(unique_ptr<TreeNode>*  uniq_ptr_ptr) const {
       if (*uniq_ptr_ptr == nullptr) {
           return nullptr;
       }

       if ((*uniq_ptr_ptr)->left == nullptr) {
           return uniq_ptr_ptr;
       }

       return findMin(&((*uniq_ptr_ptr)->left));
    }
};
// @exclude

#endif //ALGORITHM_ANALYSIS_INSERTION_DELETION_BST_H
