/*
 * COPPE/UFRJ (15/ABR/2021)
 * COS760 - Arquiteruas Avancadas
 * 
 * 001-TSP
 * 
 * Nome: Luiz Marcio Faria de Aquino Viana
 * DRE: 120048833
 * CPF: 024.723.347-10
 * RG: 08855128-8 IFP-RJ
 * 
 * tsp_all.h
 */

#ifndef __TSP_ALL_H
#define __TSP_ALL_H                     "__TSP_ALL_H"

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<unistd.h>
#include<ctype.h>
#include<math.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<omp.h>
#include<mpi.h> 

#include"tsp_defs.h"
#include"tsp_error.h"
#include"tsp_util.h"
#include"tsp_calc_dist.h"
#include"tsp_forcabruta.h"
#include"tsp_forcabruta_openmp.h"
#include"tsp_forcabruta_openmpi.h"
#include"tsp_algo_completo.h"
#include"tsp_algo_completo_openmp.h"
#include"tsp_algo_completo_openmpi.h"
#include"tsp_heuristica.h"
#include"tsp_heuristica_openmp.h"
#include"tsp_heuristica_openmpi.h"
#include"tsp_appmain.h"

#endif
