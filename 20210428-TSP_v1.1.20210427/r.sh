#!/bin/sh
MPIRUN=/usr/local/bin/mpirun

TIMESTAMP=$(date +%Y%m%d_%H%M%S)

OUTPUTFILE_2P=./001-RESULTADOS-TSP-2P-$TIMESTAMP.txt

./tsp-seq_mp-d10512 >> $OUTPUTFILE_2P
./tsp-seq_mp-d12512 >> $OUTPUTFILE_2P
./tsp-seq_mp-d14512 >> $OUTPUTFILE_2P
./tsp-seq_mp-d16512 >> $OUTPUTFILE_2P
./tsp-seq_mp-d18512 >> $OUTPUTFILE_2P

$MPIRUN -np 2 ./tsp-seq_mpi-d10512 >> $OUTPUTFILE_2P
$MPIRUN -np 2 ./tsp-seq_mpi-d12512 >> $OUTPUTFILE_2P
$MPIRUN -np 2 ./tsp-seq_mpi-d14512 >> $OUTPUTFILE_2P
$MPIRUN -np 2 ./tsp-seq_mpi-d16512 >> $OUTPUTFILE_2P
$MPIRUN -np 2 ./tsp-seq_mpi-d18512 >> $OUTPUTFILE_2P

