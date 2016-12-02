#ifndef ALGORITHM_ANALYSIS_HASH_TABLES_BOOT_CAMP_H
#define ALGORITHM_ANALYSIS_HASH_TABLES_BOOT_CAMP_H

#include <string>
#include <functional>
#include <unordered_set>

using std::string;
using std::unordered_set;
using std::hash;
using std::function;

// See Hash_dictionary.h
// See Anagrams.h
// See merge_contacts.h

struct Record {
    string name;
    int val;
};

struct Nocase_hash {
    int d = 1; // shift code d number of bits in each iteration
    size_t operator()(const Record& r) const {
        size_t h = 0;
        for (auto x : r.name) {
            h <<= d;
            h^= toupper(x);
        }
        return h;
    }
};

// for the reason to use equal operator
// see: http://stackoverflow.com/questions/39107488/what-is-keyequal-in-stdunordered-set-for
struct Nocase_equal {
    bool operator()(const Record& r, const Record& r2) const {
        if (r.name.size() != r2.name.size()) return false;

        for (int i = 0; i < r.name.size(); ++i) {
            if(toupper(r.name[i]) != toupper(r2.name[i]))
                return false;
        }

        return true;
    }
};

unordered_set<Record, Nocase_hash, Nocase_equal> m {
        20,  /* bucket count */
        Nocase_hash{2},
        Nocase_equal{}
};

//{{"andy", 7}, {"al", 9}, {"bill", -3}, {"barbara", 12}}
unordered_set<Record, Nocase_hash, Nocase_equal> m1 {
        // use bucket count 4, Nocase_hash{} and Nocase_equal{}
};

size_t hf(const Record& r) {
    return hash<string>()(r.name)^hash<int>()(r.val);
}

bool eq(const Record& r, const Record& r2) {
    return r.name == r2.name && r.val == r2.val;
}

// Not work: unordered_set<Record, decltype(hf), decltype(eq)> m2 {
unordered_set<Record, decltype(&hf), decltype(&eq)> m2 {
        20, /*bucket count */
        hf,
        eq
};

unordered_set<Record,   // order type
        function<size_t(const Record&)>,    // hash type
        function<bool(const Record&, const Record&)>    // equal type
        > m3 { 10,
                [](const Record& r) {return hash<string>{}(r.name) ^ hash<int>{}(r.val); },
                [](const Record& r, const Record& r2) {return r.name == r2.name && r.val == r2.val;}
};

auto hf1 = [](const Record& r) {return hash<string>{}(r.name) ^ hash<int>{}(r.val); };
auto eq1 = [](const Record& r, const Record& r2) {return r.name == r2.name && r.val == r2.val; };

unordered_set<Record, decltype(hf1), decltype(eq1)> m4 {10, hf1, eq1};


#endif //ALGORITHM_ANALYSIS_HASH_TABLES_BOOT_CAMP_H
