#!/bin/bash
mkdir -p build
gcc ../sum16.c -o build/sum16.exe
cd build
./sum16.exe
