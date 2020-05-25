# Dijkstra-algorithm
### Name: Junrui Zhu/Danh Nguyen
CMPUT275, Winter 2019
Assignment2 part1: Server

### Introduction
Dikstra algorithm, to find least cost path in a graph.
Program designed as backbone for server feedback of the Edmonton pathfinder Arduino interface project, can be used as C++ terminal program on Ubuntu (Windows not tested).

![alt text](https://github.com/danny-cpp/Dijkstra-algorithm/blob/master/result_on_Arduino.gif?raw=true)


### include file:      
- READEME
- digraph.h
- dijkstra.cpp
- dijkstra.h
- heap.h
- server.cpp
- wdigraph.h
- Makefile
- edmonton-roads-2.0.1.txt

### Running process:
1. type "make" in the terminal.
2. Needs "edmonton-roads-2.0.1.txt" (provided) to run.
3. Use argument: ./server < input.txt > output.txt to construct output text file.
4. Use make clean to remove objectives and executable.

### Acknowledgement:
Edmonton graph data (edmonton-roads-2.0.1.txt) is provided. Graph and Heap class from our own previous works. Files used under permission of CMPUT275 course University of Alberta. All rights reserved.


