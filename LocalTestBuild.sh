#!/bin/bash

g++ -std=c++0x -I /home/boost_1_54_0/ -fopenmp MainFile.cpp BCell.cpp Islet.cpp -o Beta.exe
./Beta.exe
