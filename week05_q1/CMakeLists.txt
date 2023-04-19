cmake_minimum_required(VERSION 3.22)
project(week05_q1)

set(CMAKE_CXX_STANDARD 14)

add_executable(week05_q1 main.cpp WGraph.h WGraph.c popularityRank.c)
