cmake_minimum_required(VERSION 3.3)

project(Ch7_Strings C CXX)

add_definitions(-std=c++14)

set(HEADER_FILES
        strings_boot_camp.h
        interconverting_string_integer.h
        Convert_base.h
        Spreadsheet_encoding.h
        Replace_and_remove.h
        valid-palindrome.h
        Reverse_words.h
        Phone_mnemonic.h
        Phone_mnemonic_iterative.h
        look-and-say.h
        roman-to-integer.h
        integer-to-roman.h
        valid-IP-address.h
        snake-string.h
        Run_length_compression.h
        Run_length_compression_google.h
        rabin-karp.h
        )

set(SOURCE_FILES
        ../dummy.cpp
        )

add_library(Ch7_Strings STATIC ${SOURCE_FILES} ${HEADER_FILES})