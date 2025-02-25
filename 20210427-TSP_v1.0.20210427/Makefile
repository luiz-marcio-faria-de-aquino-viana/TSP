
CC = /usr/local/bin/mpicc
#CC = /usr/bin/gcc
CFLAGS = -ggdb -O0 -Wall -fopenmp
LFLAGS = -ggdb -lstdc++ -lgomp -lm

OBJS = tsp_error.o tsp_util.o tsp_calc_dist.o tsp_forcabruta.o tsp_forcabruta_openmp.o tsp_forcabruta_openmpi.o tsp_algo_completo.o tsp_algo_completo_openmp.o tsp_algo_completo_openmpi.o tsp_heuristica.o tsp_heuristica_openmp.o tsp_heuristica_openmpi.o tsp_appmain.o tsp.o

all:			$(OBJS)
				$(CC) $(OBJS) $(LFLAGS) -o tsp

bak:
				rm -f *~

clean:
				rm -f tsp
				rm -f *o

rebuild:
				make clean
				make all

log:
				rm *.log

tsp.o:			tsp_all.h						\
				tsp_defs.h						\
				tsp_error.h						\
				tsp_error.cpp					\
				tsp_util.h						\
				tsp_util.cpp					\
				tsp_calc_dist.h					\
				tsp_calc_dist.cpp				\
				tsp_forcabruta.h				\
				tsp_forcabruta.cpp				\
				tsp_forcabruta_openmp.h			\
				tsp_forcabruta_openmp.cpp		\
				tsp_forcabruta_openmpi.h		\
				tsp_forcabruta_openmpi.cpp		\
				tsp_algo_completo.h				\
				tsp_algo_completo.cpp			\
				tsp_algo_completo_openmp.h		\
				tsp_algo_completo_openmp.cpp	\
				tsp_algo_completo_openmpi.h		\
				tsp_algo_completo_openmpi.cpp	\
				tsp_heuristica.h				\
				tsp_heuristica.cpp				\
				tsp_heuristica_openmp.h			\
				tsp_heuristica_openmp.cpp		\
				tsp_heuristica_openmpi.h		\
				tsp_heuristica_openmpi.cpp		\
				tsp_appmain.h					\
				tsp_appmain.cpp					\
				tsp.cpp
				$(CC) $(CFLAGS) -c tsp_error.cpp
				$(CC) $(CFLAGS) -c tsp_util.cpp
				$(CC) $(CFLAGS) -c tsp_calc_dist.cpp
				$(CC) $(CFLAGS) -c tsp_forcabruta.cpp
				$(CC) $(CFLAGS) -c tsp_forcabruta_openmp.cpp
				$(CC) $(CFLAGS) -c tsp_forcabruta_openmpi.cpp
				$(CC) $(CFLAGS) -c tsp_algo_completo.cpp
				$(CC) $(CFLAGS) -c tsp_algo_completo_openmp.cpp
				$(CC) $(CFLAGS) -c tsp_algo_completo_openmpi.cpp
				$(CC) $(CFLAGS) -c tsp_heuristica.cpp
				$(CC) $(CFLAGS) -c tsp_heuristica_openmp.cpp
				$(CC) $(CFLAGS) -c tsp_heuristica_openmpi.cpp
				$(CC) $(CFLAGS) -c tsp_appmain.cpp
				$(CC) $(CFLAGS) -c tsp.cpp
