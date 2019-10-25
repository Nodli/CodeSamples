#!/bin/bash
mkdir -p build
g++ main.cpp ../bmp.cpp -I .. -o build/bmp.exe
cd build
./bmp.exe
