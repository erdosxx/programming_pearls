#ifndef ALGORITHM_ANALYSIS_BINARY_TREE_LOCK_H
#define ALGORITHM_ANALYSIS_BINARY_TREE_LOCK_H
//10.17 Implement locking in a binary tree

#include <memory>

using std::make_shared;
using std::shared_ptr;

namespace lock_tree {
// @include
    class BinaryTreeNode {
    public:
        bool IsLocked() const { return locked_; }

        bool Lock() {
            // We cannot lock if any of this node's descendants are locked.
            if (numLockedDescendants_ > 0 || locked_) {
                return false;
            }

            // We cannot lock if any of this node's ancestors are locked.
            for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
                if (iter->locked_) {
                    return false;
                }
            }

            // Lock this node and increments all its ancestors's descendant lock
            // counts.
            locked_ = true;
            for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
                ++iter->numLockedDescendants_;
            }
            return true;
        }

        void Unlock() {
            if (locked_) {
                // Unlocks itself and decrements its ancestors's descendant lock counts.
                locked_ = false;
                for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
                    --iter->numLockedDescendants_;
                }
            }
        }

        // @exclude
        shared_ptr<BinaryTreeNode> &left() { return left_; }

        shared_ptr<BinaryTreeNode> &right() { return right_; }

        shared_ptr<BinaryTreeNode> &parent() { return parent_; }
        // @include
    private:
        shared_ptr<BinaryTreeNode> left_, right_, parent_;

        bool locked_ = false;
        int numLockedDescendants_ = 0;
    };
// @exclude

}

#endif //ALGORITHM_ANALYSIS_BINARY_TREE_LOCK_H
