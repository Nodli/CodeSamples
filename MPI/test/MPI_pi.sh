#!/bin/bash
mkdir -p build
mpicc ../MPI_pi.c -o build/pi.exe
cd build
mpiexec -n 4 ./pi.exe 100000
