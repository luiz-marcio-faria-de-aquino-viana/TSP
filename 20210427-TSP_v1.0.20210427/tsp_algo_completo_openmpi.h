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
 * tsp_algo_completo_openmpi.h
 */

#ifndef __TSP_ALGO_COMPLETO_OPENMPI_H
#define __TSP_ALGO_COMPLETO_OPENMPI_H                              "__TSP_ALGO_COMPLETO_OPENMPI_H"

class CTSPAlgoCompletoOpenMPI
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

    CTSPAlgoCompletoOpenMPI(
        int appid, 
        int nprocs, 
        int ftype, 
        datatest_t* result, 
        datatokenptr_t* datawrk, 
        datatokenptr_t* datares, 
        long datasz);
    ~CTSPAlgoCompletoOpenMPI();

    /* Methodes */

    double calculateCost(datatokenptr_t* datawrk, long datasz);

    void copyWorkToResultData(datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz);

    void resetResultData();

    void executeStep(long i, long j, datatokenptr_t* datawrk, long datasz);

    void execute();

    void debugWorkData(datatokenptr_t* datawrk, long datasz);

};

#endif
