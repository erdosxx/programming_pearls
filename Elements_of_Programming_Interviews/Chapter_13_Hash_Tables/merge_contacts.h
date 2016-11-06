#ifndef ALGORITHM_ANALYSIS_MERGE_CONTACTS_H
#define ALGORITHM_ANALYSIS_MERGE_CONTACTS_H
// 13 Hash Tables boot camp

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

using std::hash;
using std::string;
using std::unordered_set;
using std::vector;

// @include
struct ContactList {
    // Equal function for hash.
    bool operator==(const ContactList& that) const {
        return unordered_set<string>(names.begin(), names.end()) ==
               unordered_set<string>(that.names.begin(), that.names.end());
    }

    vector<string> names;
};

// Hash function for ContactList.
struct HashContactList {
    size_t operator()(const ContactList& contacts) const {
        size_t hash_code = 0;

        for (const string& name : unordered_set<string>(contacts.names.begin(),
                                                        contacts.names.end())) {
            hash_code ^= hash<string>()(name);
        }

        return hash_code;
    }
};

vector<ContactList> MergeContactLists(const vector<ContactList>& contacts) {
    unordered_set<ContactList, HashContactList> unique_contacts(
            contacts.begin(), contacts.end());

    return {unique_contacts.begin(), unique_contacts.end()};
    //return vector<ContactList>{unique_contacts.begin(), unique_contacts.end()};
}
// @exclude

#endif //ALGORITHM_ANALYSIS_MERGE_CONTACTS_H
