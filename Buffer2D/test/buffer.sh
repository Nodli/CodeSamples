#!/bin/bash
mkdir -p build
g++ main.cpp -I .. -o build/buffer.exe -O2
cd build
./buffer.exe
