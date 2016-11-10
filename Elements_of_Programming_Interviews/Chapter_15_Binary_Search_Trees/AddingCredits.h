#ifndef ALGORITHM_ANALYSIS_ADDINGCREDITS_H
#define ALGORITHM_ANALYSIS_ADDINGCREDITS_H
// 15.13 Add credits

#include <map>
#include <string>
#include <unordered_set>
#include <unordered_map>

using std::map;
using std::string;
using std::unordered_map;
using std::unordered_set;

// @include
class ClientsCreditsInfo {
public:
    void Insert(const string& client_id, int c) {
        Remove(client_id);
        // for offset_ see Lookup code. When we return credit, we add offset_ to credit.
        client_to_credit_.emplace(client_id, c - offset_);
        credit_to_clients_[c - offset_].emplace(client_id);
    }

    bool Remove(const string& client_id) {
        auto credit_iter = client_to_credit_.find(client_id);
        if (credit_iter != client_to_credit_.end()) {
            credit_to_clients_[credit_iter->second].erase(client_id);

            if (credit_to_clients_[credit_iter->second].empty()) {
                credit_to_clients_.erase(credit_iter->second);
            }
            client_to_credit_.erase(credit_iter);
            return true;
        }
        return false;
    }

    int Lookup(const string& client_id) const {
        auto credit_iter = client_to_credit_.find(client_id);
        return credit_iter == client_to_credit_.cend()
               ? -1
               : credit_iter->second + offset_;
    }

    void AddAll(int C) { offset_ += C; }

    string Max() const {
        auto iter = credit_to_clients_.crbegin();
        return iter == credit_to_clients_.crend() || iter->second.empty()
               ? ""
               : *(iter->second.cbegin());
    }

private:
    int offset_ = 0;
    unordered_map<string, int> client_to_credit_;
    map<int, unordered_set<string>> credit_to_clients_;
};
// @exclude

#endif //ALGORITHM_ANALYSIS_ADDINGCREDITS_H
