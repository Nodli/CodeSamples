#!/bin/bash
mpicc ../src/MPI_max.c -lm -o max
mpiexec -n 4 max 99
