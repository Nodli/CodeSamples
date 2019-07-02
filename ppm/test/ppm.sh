#!/bin/bash
mkdir -p build
g++ main.cpp ../ppm.cpp -I .. -o build/ppm.exe
cd build
./ppm.exe
