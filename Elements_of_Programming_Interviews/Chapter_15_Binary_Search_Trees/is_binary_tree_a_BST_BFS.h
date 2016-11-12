#ifndef ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_BFS_H
#define ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_BFS_H
// 15.1 Test if a binary tree satisfies the BST property

#include <limits>
#include <memory>
#include <queue>

#include "Binary_tree_prototype.h"

using std::numeric_limits;
using std::queue;
using std::unique_ptr;

namespace bfs {
// @include
    struct QueueEntry {
        const unique_ptr<BinaryTreeNode<int>>& tree_node;
        int lower_bound, upper_bound;
    };

    bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>> &tree) {
        queue<QueueEntry> BFS_queue;
        BFS_queue.emplace(QueueEntry{tree, numeric_limits<int>::min(),
                                     numeric_limits<int>::max()});

        while (!BFS_queue.empty()) {
            if (BFS_queue.front().tree_node.get()) {
                //if (BFS_queue.front().tree_node->data < BFS_queue.front().lower_bound ||
                //    BFS_queue.front().tree_node->data > BFS_queue.front().upper_bound) {
                if (! (BFS_queue.front().lower_bound <= BFS_queue.front().tree_node->data &&
                        BFS_queue.front().tree_node->data <= BFS_queue.front().upper_bound) ) {
                    return false;
                }

                BFS_queue.emplace(QueueEntry{BFS_queue.front().tree_node->left,
                                             BFS_queue.front().lower_bound,
                                             BFS_queue.front().tree_node->data});
                BFS_queue.emplace(QueueEntry{BFS_queue.front().tree_node->right,
                                             BFS_queue.front().tree_node->data,
                                             BFS_queue.front().upper_bound});
            }
            BFS_queue.pop();
        }
        return true;
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_IS_BINARY_TREE_A_BST_BFS_H
