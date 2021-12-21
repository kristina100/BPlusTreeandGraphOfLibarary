cmake_minimum_required(VERSION 3.20)
project(Bplustree)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bplustree main.cpp
        Header/FileDo.h
        Header/BPlusTree.h
        Source/FileDo.cpp
        Source/BPlusTree.cpp
        )
