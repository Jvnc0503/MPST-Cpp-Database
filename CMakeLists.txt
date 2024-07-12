cmake_minimum_required(VERSION 3.28)
project(MPST_Cpp_Database)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(MPST_Cpp_Database main.cpp
        Movie.h
        MovieBuilder.h
        MovieDatabase.h
        Node.h
        Trie.h)
