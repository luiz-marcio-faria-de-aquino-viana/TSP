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
 * tsp_calc_dist.cpp
 */

#include"tsp_all.h"

/* DISTANCE FUNCTIONS
 */
double calculateEuclideanDistance(datatoken_t* p1, datatoken_t* p2)
{
    double xd = p2->datatoken_xp - p1->datatoken_xp;
    double yd = p2->datatoken_yp - p1->datatoken_yp;

    double result = round(sqrt(xd * xd + yd * yd));
    //printf("\nEuclideanDistance: %lf", result);

    return result;
}

double calculateManhattanDistance(datatoken_t* p1, datatoken_t* p2)
{
    double xd = abs(p2->datatoken_xp - p1->datatoken_xp);
    double yd = abs(p2->datatoken_yp - p1->datatoken_yp);

    double result = round(xd + yd);
    //printf("\nManhattanDistance: %lf", result);

    return result;
}

double calculateMaximumDistance(datatoken_t* p1, datatoken_t* p2)
{
    double xd = abs(p2->datatoken_xp - p1->datatoken_xp);
    double yd = abs(p2->datatoken_yp - p1->datatoken_yp);

    double result = MAX(round(xd), round(yd));
    //printf("\nMaximumDistance: %lf", result);

    return result;
}

double calculateGeographicalDistance(datatoken_t* p1, datatoken_t* p2)
{
    double r = 6378.1370;

    // LAT/LON - PONTO 1

    double lat_deg1 = floor(p1->datatoken_xp);
    double lat1 = M_PI * (lat_deg1 / 180.0);

    double lon_deg1 = floor(p1->datatoken_xp);
    double lon1 = M_PI * (lon_deg1 / 180.0);
    
    // LAT/LON - PONTO 2

    double lat_deg2 = floor(p2->datatoken_xp);
    double lat2 = M_PI * (lat_deg2 / 180.0);

    double lon_deg2 = floor(p2->datatoken_xp);
    double lon2 = M_PI * (lon_deg2 / 180.0);

    // CALCULA DISTANCIA GEOGRAFICA

    double q1 = cos(lon2 - lon1);
    double q2 = cos(lat2 - lat1);
    double q3 = cos(lat2 + lat1);

    double result = round(r * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
    //printf("\nGeographicalDistance: %lf", result);

    return result;
}

double calculatePseudoEuclideanDistance(datatoken_t* p1, datatoken_t* p2)
{
    double xd = p2->datatoken_xp - p1->datatoken_xp;
    double yd = p2->datatoken_yp - p1->datatoken_yp;

    double dist1 = sqrt(xd * xd + yd * yd);
    double dist2 = round(dist1);

    double result = (dist2 < dist1) ? dist2 + 1 : dist2;
    //printf("\nPseudoEuclideanDistance: %lf", result);

    return result;
}

double calculateCeilingEuclideanDistance(datatoken_t* p1, datatoken_t* p2)
{
    double xd = p2->datatoken_xp - p1->datatoken_xp;
    double yd = p2->datatoken_yp - p1->datatoken_yp;

    double result = ceil(sqrt(xd * xd + yd * yd));
    //printf("\nCeilingEuclideanDistance: %lf", result);

    return result;
}

/* DISTANCE FUNCTIONS (PRINCIPAL)
 */
double calculateEuclideanDistance(int ftype, datatoken_t* p1, datatoken_t* p2)
{
    double result = -1.0;

    if(ftype == TSP_CALC_EUCL_DIST)
        result = calculateEuclideanDistance(p1, p2);
    if(ftype == TSP_CALC_MANH_DIST)
        result = calculateManhattanDistance(p1, p2);
    if(ftype == TSP_CALC_MAX_DIST)
        result = calculateMaximumDistance(p1, p2);
    if(ftype == TSP_CALC_GEO_DIST)
        result = calculateGeographicalDistance(p1, p2);
    if(ftype == TSP_CALC_PSEUDO_EUCL_DIST)
        result = calculatePseudoEuclideanDistance(p1, p2);
    if(ftype == TSP_CALC_CEIL_EUCL_DIST)
        result = calculateCeilingEuclideanDistance(p1, p2);

    return result;
}
