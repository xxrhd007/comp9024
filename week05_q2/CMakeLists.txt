cmake_minimum_required(VERSION 3.22)
project(week05_q2)

set(CMAKE_CXX_STANDARD 14)

add_executable(week05_q2 main.cpp dijkstra.c PQueue.h PQueue.c WGraph.h WGraph.c)
