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

#ifndef __TSP_HEURISTICA_OPENMP_H
#define __TSP_HEURISTICA_OPENMP_H                             "__TSP_HEURISTICA_OPENMP_H"

class CTSPHeuristicaOpenMP
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

    CTSPHeuristicaOpenMP(
        int appid, 
        int nprocs, 
        int ftype, 
        datatest_t* result, 
        datatokenptr_t* datawrk, 
        datatokenptr_t* datares, 
        long datasz);
    ~CTSPHeuristicaOpenMP();

    long findItemAt(long currpos, long* tidStartData);

    double calculateMinCost(datatokenptr_t* p1, datatokenptr_t* p2, datatokenptr_t* datawrk, long datasz, long* tidStartData);

    double calculateTotalCost(datatokenptr_t* data, long datasz);

    void resetResultData(datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz);

    void execute();

    void debugWorkData(datatokenptr_t* data, long size);

};

#endif
