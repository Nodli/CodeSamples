#!/bin/bash
mkdir -p build
mpicc ../MPI_max.c -lm -o build/max.exe
cd build
mpiexec -n 4 ./max.exe 99
