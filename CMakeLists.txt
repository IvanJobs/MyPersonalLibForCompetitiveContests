cmake_minimum_required(VERSION 3.5)

project(PersonalLib)

set(CMAKE_CXX_FLAGS " -std=c++11 -g ")
link_libraries(gtest)
# disjoint set
add_executable(disjoin_set_test
    disjoint_set_test.cpp  
)

# binary search tree
add_executable(bst_test 
   binary_search_tree_test.cpp
)

# binary heap
add_executable(bh_test
    binary_heap_test.cpp)

# trie
add_executable(trie_test
    trie_test.cpp)

# treap 
add_executable(treap_test
    treap_test.cpp)

# fenwick 
add_executable(fenwick_test
    binary_index_tree_test.cpp)

# radix sort
add_executable(radix_test 
    radix_sort_test.cpp)

# fast power 
add_executable(fast_power
    fast_power_test.cpp)

# suffix array
add_executable(sa_test
    suffix_array_test.cpp)

# kmp 
add_executable(kmp_test
    kmp_test.cpp)

# tarjan sparse table
add_executable(tarjan_st_test
    tarjan_sparse_table_test.cpp)

# segment tree
add_executable(segment_tree_test
    segment_tree_test.cpp)

# ac autometa
add_executable(ac_test
    ac_automata_test.cpp)

# ex_gcd
add_executable(exgcd_test
    ex_gcd_test.cpp)

# interval tree 
add_executable(interval_tree_test
    interval_tree_test.cpp)
