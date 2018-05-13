cmake_minimum_required(VERSION 3.5)

project(PersonalLib)

set(CMAKE_CXX_FLAGS " -std=c++11 ")
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

target_link_libraries(trie_test
    gtest)


# treap 
add_executable(treap_test
    treap_test.cpp)

target_link_libraries(treap_test
    gtest)
# fenwick 
add_executable(fenwick_test
    binary_index_tree_test.cpp)

target_link_libraries(fenwick_test
    gtest)

