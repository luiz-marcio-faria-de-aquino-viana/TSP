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
 * tsp_heuristica.h
 */

#ifndef __TSP_HEURISTICA_H
#define __TSP_HEURISTICA_H                             "__TSP_HEURISTICA_H"

class CTSPHeuristica
{
private:
    datatest_t* m_result;

    datatokenptr_t* m_datawrk;
    datatokenptr_t* m_datares;
    long m_datasz;

    int m_appid;
    int m_nprocs;

    int m_ftype;

public:

    CTSPHeuristica(
        int appid, 
        int nprocs, 
        int ftype, 
        datatest_t* result, 
        datatokenptr_t* datawrk, 
        datatokenptr_t* datares, 
        long datasz);
    ~CTSPHeuristica();

    double calculateMinCost(datatokenptr_t* p1, datatokenptr_t* p2);

    void resetResultData();

    void debugWorkData(datatokenptr_t* data, long size);

    void execute();

};

#endif
