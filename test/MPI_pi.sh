#!/bin/bash
mpicc ../src/MPI_pi.c -o pi
mpiexec -n 4 pi 100000
