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
 * tsp_forcabruta_openmp.h
 */

#ifndef __TSP_FORCABRUTA_OPENMP_H
#define __TSP_FORCABRUTA_OPENMP_H                              "__TSP_FORCABRUTA_OPENMP_H"

class CTSPForcaBrutaOpenMP
{
private:
    datatest_t* m_result;

    datatokenptr_t** m_datawrk;
    datatokenptr_t** m_datares;
    long m_datasz;

    int m_appid;
    int m_nprocs;

    int m_ftype;

public:

    CTSPForcaBrutaOpenMP(
        int appid, 
        int nprocs, 
        int ftype, 
        datatest_t* result, 
        datatokenptr_t** datawrk, 
        datatokenptr_t** datares, 
        long datasz);
    ~CTSPForcaBrutaOpenMP();

    /* Methodes */

    double calculateCost(datatokenptr_t* datawrk, long datasz);

    void avaliateTotalCost(int tid, double* initial_cost, double* min_cost, datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz);

    void mergeResultData(datatokenptr_t* p_dst, datatokenptr_t* p_src, long datasz);

    void copyWorkToResultData(datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz);

    void resetResultData(datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz);

    long validData(datatokenptr_t* datawrk, long datasz);

    long executeStep(long inival, long finval, datatokenptr_t* datawrk, long datasz);

    void execute();

    void debugWorkData(int tid, datatokenptr_t* datawrk, long datasz);

};

#endif
