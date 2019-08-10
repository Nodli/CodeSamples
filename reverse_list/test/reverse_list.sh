#!/bin/bash
mkdir -p build
gcc ../reverse_list.c -o build/reverse_list.exe
cd build
./reverse_list.exe
