#!/bin/sh
export GOMP_CPU_AFFINITY=0-1
make clean; make all;

#make clean; make all; mv ./tsp ./tsp-seq_openmp-a5
#make clean; make all; mv ./tsp ./tsp-seq_openmp-a6
#make clean; make all; mv ./tsp ./tsp-seq_openmp-a7
#make clean; make all; mv ./tsp ./tsp-seq_openmp-a8
#make clean; make all; mv ./tsp ./tsp-seq_openmp-a9
#
#make clean; make all; mv ./tsp ./tsp-seq_openmpi-a5
#make clean; make all; mv ./tsp ./tsp-seq_openmpi-a6
#make clean; make all; mv ./tsp ./tsp-seq_openmpi-a7
#make clean; make all; mv ./tsp ./tsp-seq_openmpi-a8
#make clean; make all; mv ./tsp ./tsp-seq_openmpi-a9
#
#make clean; make all; mv ./tsp ./tsp-seq_openmp-d10512

