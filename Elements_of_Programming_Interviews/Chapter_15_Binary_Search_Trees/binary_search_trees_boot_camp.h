#ifndef ALGORITHM_ANALYSIS_BINARY_SEARCH_TREES_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_BINARY_SEARCH_TREES_BOOT_CAMP_H
// 15. Binary Search Trees Boot Camp

#include <string>
#include <functional>
#include "BST_prototype.h"

using std::string;
using std::function;


BSTNode<int>* SearchBST(const unique_ptr<BSTNode<int>>& tree, int key) {
    if (tree == nullptr) {
        return nullptr;
    }

    if(tree->data == key) {
        return tree.get();
    }

    return key < tree->data ? SearchBST(tree->left, key)
            : SearchBST(tree->right, key);
}

struct student {
    string name;
    int score;
};

// Method 1: compare object
struct Comp_by_score {
    bool operator()(const student* a_ptr, const student* b_ptr) {
        return a_ptr->score < b_ptr->score;
    }
};

struct Comp_by_name {
    bool operator()(const student* a_ptr, const student* b_ptr) {
        return a_ptr->name < b_ptr->name;
    }
};

// Method 2: function pointer
bool compare_by_name(const student* a_ptr, const student* b_ptr) {
    return a_ptr->name < b_ptr->name;
}

bool compare_by_score(const student* a_ptr, const student* b_ptr) {
    return a_ptr->score < b_ptr->score;
}

// Method 3: functional object

auto comp_score = [](const student* a_ptr, const student* b_ptr) -> bool {
    return a_ptr->score < b_ptr->score;
};

#endif //ALGORITHM_ANALYSIS_BINARY_SEARCH_TREES_BOOT_CAMP_H
