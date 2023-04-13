cmake_minimum_required(VERSION 3.24.2)
project(lab4a C)

set(CMAKE_C_STANDARD 99)

add_executable(lab4a main.c bst_mngr.c bst_mngr.h aux_funcs.c aux_funcs.h)
