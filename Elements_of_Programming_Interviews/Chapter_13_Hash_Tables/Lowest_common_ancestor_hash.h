#ifndef ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_HASH_H
#define ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_HASH_H
// 13.4 Compute the LCA, optimizing for close ancestors

#include <memory>
#include <stdexcept>
#include <unordered_set>

#include "Binary_tree_with_parent_prototype.h"

using std::invalid_argument;
using std::unique_ptr;
using std::unordered_set;
using btree_with_parent::BinaryTreeNode;

// @include
BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node_0,
                         const unique_ptr<BinaryTreeNode<int>>& node_1) {
    auto *iter_0 = node_0.get();
    auto *iter_1 = node_1.get();

    unordered_set<const BinaryTreeNode<int>*> nodes_on_path_to_root;

    while (iter_0 || iter_1) {
    // Ascend tree in tandem for these two nodes.
        if (iter_0) {
            // if iter_0 is already checked
            // pair <iterator,bool> emplace
            // if the element is exist, second  set false.
            if (nodes_on_path_to_root.emplace(iter_0).second == false) {
                return iter_0;
            }
            iter_0 = iter_0->parent;
        }

        if (iter_1) {
            if (nodes_on_path_to_root.emplace(iter_1).second == false) {
                return iter_1;
            }
            iter_1 = iter_1->parent;
        }
    }
    throw invalid_argument("node_0 and node_1 are not in the same tree");
}
// @exclude

#endif //ALGORITHM_ANALYSIS_LOWEST_COMMON_ANCESTOR_HASH_H
