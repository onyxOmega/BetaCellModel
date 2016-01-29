#!/bin/bash

g++ -I  /home/boost_1_54_0/ -fopenmp MainFile.cpp -o Beta
./Beta >> out.txt
