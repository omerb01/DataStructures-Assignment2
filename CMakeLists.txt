cmake_minimum_required(VERSION 3.10)
project(DataStructures_HW2)

set(CMAKE_CXX_STANDARD 11)

add_executable(DataStructures_HW2 library2.h main.cpp Oasis.h AVLTree.h exceptions.h HashTable.h MinHeap.h)
