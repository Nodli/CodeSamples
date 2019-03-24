#!/bin/bash

mpicc pi.c -o pi
mpiexec -n 4 pi 100000
