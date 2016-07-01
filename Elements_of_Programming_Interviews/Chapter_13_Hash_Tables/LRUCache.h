#ifndef ALGORITHM_ANALYSIS_LRUCACHE_H
#define ALGORITHM_ANALYSIS_LRUCACHE_H

#include <list>
#include <unordered_map>

using std::list;
using std::pair;
using std::unordered_map;

// @include
template <size_t capacity>
class LRUCache {
public:
    bool Lookup(int isbn, int* price) {
        auto it = isbn_price_table_.find(isbn);
        if (it == isbn_price_table_.end()) {
            return false;
        }

        *price = it->second.second;
        // Since key has just been accessed, move it to the front.
        MoveToFront(isbn, it);
        return true;
    }

    void Insert(int isbn, int price) {
        auto it = isbn_price_table_.find(isbn);
        // We add the value for key only if key is not present - we don't update
        // existing values.
        if (it != isbn_price_table_.end()) {
            // Specification says we should make isbn the most recently used.
            MoveToFront(isbn, it);
        } else {
            if (isbn_price_table_.size() == capacity) {
                // Removes the least recently used ISBN to get space.
                isbn_price_table_.erase(lru_queue_.back());
                lru_queue_.pop_back();
            }
            lru_queue_.emplace_front(isbn);
            isbn_price_table_[isbn] = {lru_queue_.begin(), price};
        }
    }

    bool Erase(int isbn) {
        auto it = isbn_price_table_.find(isbn);
        if (it == isbn_price_table_.end()) {
            return false;
        }

        lru_queue_.erase(it->second.first);
        isbn_price_table_.erase(it);
        return true;
    }

private:
    using Table =  unordered_map<int, pair<list<int>::iterator, int>>;

    // Forces this key-value pair to move to the front.
    void MoveToFront(int isbn, const Table::iterator& it) {
        // list: iterator erase (const_iterator position);
        lru_queue_.erase(it->second.first);
        lru_queue_.emplace_front(isbn);
        it->second.first = lru_queue_.begin();
    }

    Table isbn_price_table_;
    list<int> lru_queue_;
};
// @exclude

#endif //ALGORITHM_ANALYSIS_LRUCACHE_H
