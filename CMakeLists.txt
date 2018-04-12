cmake_minimum_required(VERSION 3.5)

project(PersonalLib)

set(CMAKE_CXX_FLAGS " -std=c++11 ")
# disjoint set
add_executable(disjoin_set_test
    disjoint_set_test.cpp  
)
