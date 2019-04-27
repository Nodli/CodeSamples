#!/bin/bash
mpicc MPI_max.c -lm -o max.exe
mpiexec -n 4 max.exe 99
