cmake_minimum_required(VERSION 3.3)

project(Ch13_Hash_Tables C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        hash_tables_boot_camp.h
        Hash_dictionary.h
        Anagrams.h
        anagrams_needle_haystack.h
        merge_contacts.h
        Can_string_be_palindrome_hash.h
        Can_string_be_palindrome_sorting.h
        Anonymous_letter.h
        LRUCache.h
        Lowest_common_ancestor_hash.h
        Nearest_repetition.h
        Smallest_subarray_covering_set.h
        Smallest_subarray_covering_set_stream.h
        Subseq_cover.h
        longest-subarray-with-distinct-entries.h
        longest-contained-range.h
        average-top-3-scores.h
        substring-with-concatenation-of-all-words.h
        Collatz_conjecture.h
        )

#set(SOURCE_FILES
#        bitsort.cpp bitsortgen.cpp qsortints.cpp sortints.cpp spacebitsort.cpp
#        )

add_library(Ch13_Hash_Tables STATIC ${SOURCE_FILES} ${HEADER_FILES})