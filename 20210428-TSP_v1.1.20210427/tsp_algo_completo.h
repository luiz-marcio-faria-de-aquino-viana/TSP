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
 * tsp_algo_completo.h
 */

#ifndef __TSP_ALGO_COMPLETO_H
#define __TSP_ALGO_COMPLETO_H                              "__TSP_ALGO_COMPLETO_H"

class CTSPAlgoCompleto
{
private:
    datatest_t* m_result;

    datatokenptr_t* m_datawrk;
    datatokenptr_t* m_datainv;
    datatokenptr_t* m_datares;
    long m_datasz;

    int m_appid;
    int m_nprocs;

    int m_ftype;

public:

    CTSPAlgoCompleto(
        int appid, 
        int nprocs, 
        int ftype, 
        datatest_t* result, 
        datatokenptr_t* datawrk, 
        datatokenptr_t* datainv, 
        datatokenptr_t* datares, 
        long datasz);
    ~CTSPAlgoCompleto();

    /* Methodes */

    double calculateCost(datatokenptr_t* datawrk, long datasz);

    void avaliateTotalCost(double* initial_cost, double* min_cost, datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz);

    void copyWorkToResultData(datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz);

    void resetResultData();

    void changeItem(long posI, long posF, datatokenptr_t* datawrk, long datasz);

    void execute_step1();
    void execute_step2();
    void execute();

    void debugWorkData(datatokenptr_t* datawrk, long datasz);

};

#endif
