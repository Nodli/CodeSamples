#!/bin/bash
mpicc max.c -lm -o max
mpiexec -n 4 max 99
