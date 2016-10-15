#ifndef ALGORITHM_ANALYSIS_HUFFMAN_ENCODING_H
#define ALGORITHM_ANALYSIS_HUFFMAN_ENCODING_H

#include <functional>
#include <queue>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using std::function;
using std::make_unique;
using std::priority_queue;
using std::unique_ptr;
using std::random_device;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

namespace huffman {

    const double kEnglishFreq[] = {
            8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
            0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
            6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074};

    struct CharWithFrequency {
        char character;
        double freq;
    };

    struct BinaryTreeNode {
        double aggregate_freq;
        CharWithFrequency *char_with_freq;
        shared_ptr<BinaryTreeNode> left, right;
    };

    void AssignHuffmanCode(const shared_ptr<BinaryTreeNode> &,
                           const unique_ptr<string> &,
                           unordered_map<char, string> *);

// @include

    unordered_map<char, string> HuffmanEncoding(
            vector<CharWithFrequency> *symbols) {
        // Initially assigns each symbol into candidates.
        // build min_heap
        priority_queue<
                shared_ptr<BinaryTreeNode>, vector<shared_ptr<BinaryTreeNode>>,
                function<bool(shared_ptr<BinaryTreeNode>, shared_ptr<BinaryTreeNode>)>
                > candidates([](const shared_ptr<BinaryTreeNode> &lhs,
                              const shared_ptr<BinaryTreeNode> &rhs) {
            return lhs->aggregate_freq > rhs->aggregate_freq;
        });

        for (auto &s : *symbols) {
            candidates.emplace(new BinaryTreeNode{s.freq, &s, nullptr, nullptr});
        }

        // Keeps combining two nodes until there is one node left.
        while (candidates.size() > 1) {
            shared_ptr<BinaryTreeNode> left = candidates.top();
            candidates.pop();
            shared_ptr<BinaryTreeNode> right = candidates.top();
            candidates.pop();
            candidates.emplace(new BinaryTreeNode{
                    left->aggregate_freq + right->aggregate_freq, nullptr, left, right});
        }

        unordered_map<char, string> huffman_encoding;
        // Traverses the binary tree, assigning codes to nodes.
        AssignHuffmanCode(candidates.top(), make_unique<string>(),
                          &huffman_encoding);
        return huffman_encoding;
    }

    void AssignHuffmanCode(const shared_ptr<BinaryTreeNode> &tree,
                           const unique_ptr<string> &code,
                           unordered_map<char, string> *huffman_encoding) {
        if (tree) {
            if (tree->char_with_freq) {
                // This node is a leaf.
                (*huffman_encoding)[tree->char_with_freq->character] = *code;
            } else {  // Non-leaf node.
                code->push_back('0');
                AssignHuffmanCode(tree->left, code, huffman_encoding);
                code->pop_back();
                code->push_back('1');
                AssignHuffmanCode(tree->right, code, huffman_encoding);
                code->pop_back();
            }
        }
    }
// @exclude
}

#endif //ALGORITHM_ANALYSIS_HUFFMAN_ENCODING_H
