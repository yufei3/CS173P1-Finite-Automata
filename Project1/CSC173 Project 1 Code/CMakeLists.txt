cmake_minimum_required(VERSION 3.17)
project(CSC173_Project_1_Code C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(CSC173_Project_1_Code
        save/project1.c
        BitSet.c
        BitSet.h
        dfa.c
        dfa.h
        IntHashSet.c
        IntHashSet.h
        LinkedList.c
        LinkedList.h
        nfa.c
        nfa.h
        Set.c
        Set.h
        strdup.c
        strdup.h
        tester.c)
