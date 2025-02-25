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
 * tsp_calc_dist.h
 */

#ifndef __TSP_CALC_DIST_H
#define __TSP_CALC_DIST_H                               "__TSP_CALC_DIST_H"

/* DISTANCE FUNCTIONS
 */
double calculateEuclideanDistance(datatoken_t* p1, datatoken_t* p2);

double calculateManhattanDistance(datatoken_t* p1, datatoken_t* p2);

double calculateMaximumDistance(datatoken_t* p1, datatoken_t* p2);

double calculateGeographicalDistance(datatoken_t* p1, datatoken_t* p2);

double calculatePseudoEuclideanDistance(datatoken_t* p1, datatoken_t* p2);

double calculateCeilingEuclideanDistance(datatoken_t* p1, datatoken_t* p2);

/* DISTANCE FUNCTIONS (PRINCIPAL)
 */
double calculateEuclideanDistance(int ftype, datatoken_t* p1, datatoken_t* p2);

#endif
