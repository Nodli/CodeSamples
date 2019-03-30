#!/bin/bash
mpicc MPI_pi.c -o pi.exe
mpiexec -n 4 pi.exe 100000
