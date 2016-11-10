#ifndef ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_H
#define ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_H
// 10.4 Compute the LCA when nodes have parent pointers

#include <algorithm>
#include <memory>

#include "Binary_tree_with_parent_prototype.h"

using std::make_unique;
using std::swap;
using std::unique_ptr;

namespace lca {
    using btree_with_parent::BinaryTreeNode;

    int GetDepth(const BinaryTreeNode<int>* node) {
        int depth = 0;

        while (node->parent) {
            ++depth;
            node = node->parent;
        }

        return depth;
    }

// @include
    BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node_0,
                             const unique_ptr<BinaryTreeNode<int>>& node_1) {
        BinaryTreeNode<int>* iter_0 = node_0.get();
        BinaryTreeNode<int>* iter_1 = node_1.get();
        int depth_0 = GetDepth(iter_0);
        int depth_1 = GetDepth(iter_1);

        // Makes iter_0 as the deeper node in order to simplify the code.
        if (depth_1 > depth_0) {
            swap(iter_0, iter_1);
        }

        // Ascends from the deeper node.
        int depth_diff = depth_0 - depth_1 > 0 ? depth_0 - depth_1 : depth_1 - depth_0;

        while (depth_diff--) {
            iter_0 = iter_0->parent;
        }

        // Now ascends both nodes until we reach the LCA.
        while (iter_0 != iter_1) {
            iter_0 = iter_0->parent;
            iter_1 = iter_1->parent;
        }
        return iter_0;
    }

// @exclude
}

#endif //ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_H
