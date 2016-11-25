#ifndef ALGORITHM_ANALYSIS_SHORTEST_UNIQUE_PREFIX_H
#define ALGORITHM_ANALYSIS_SHORTEST_UNIQUE_PREFIX_H
// 25.20 Find the shortest unique prefix

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using std::make_unique;
using std::unique_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;

class Trie {
public:
    virtual ~Trie() { Clear(); }

    bool Insert(const string& s) {
        auto* p = root_.get();

        for (char c : s) {
            if (p->leaves.find(c) == p->leaves.cend()) {
                p->leaves[c] = make_unique<TrieNode>(TrieNode());
            }
            p = p->leaves[c].get();
        }

        // s already existed in this trie.
        if (p->isString) {
            return false;
        } else {  // p->isString == false.
            p->isString = true;  // Inserts s into this trie.
            return true;
        }
    }

    string GetShortestUniquePrefix(const string& s) {
        auto* p = root_.get();
        string prefix;

        for (char c : s) {
            prefix += c;
            if (p->leaves.find(c) == p->leaves.cend()) {
                return prefix;
            }
            p = p->leaves[c].get();
        }

        // bug fix: return {} is not work in icpc
        return "";
    }

    void Clear() { Clear(&root_); }

private:
    struct TrieNode {
        bool isString = false;
        unordered_map<char, unique_ptr<TrieNode>> leaves;
    };

    unique_ptr<TrieNode> root_ = make_unique<TrieNode>(TrieNode());

    void Clear(unique_ptr<TrieNode>* p) {
        //for (auto& e : (*p)->leaves) {
        for (pair<const char, unique_ptr<TrieNode>>& e : (*p)->leaves) {
            if (e.second) {
                Clear(&(e.second));
            }
        }
        p->reset(nullptr);
    }
};

string FindShortestPrefix(const string& s, const unordered_set<string>& D) {
    // Builds a trie according to given dictionary D.
    Trie T;
    for (const string& word : D) {
        T.Insert(word);
    }
    return T.GetShortestUniquePrefix(s);
}

#endif //ALGORITHM_ANALYSIS_SHORTEST_UNIQUE_PREFIX_H
