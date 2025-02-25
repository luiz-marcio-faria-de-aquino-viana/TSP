/*
 * COPPE/UFRJ (15/ABR/2021)
 * COS760 - Arquiteturas Avancadas
 * 
 * 001-TSP
 * 
 * Nome: Luiz Marcio Faria de Aquino Viana
 * DRE: 120048833
 * CPF: 024.723.347-10
 * RG: 08855128-8 IFP-RJ
 * 
 * tsp_heuristica_openmpi.h
 */

#ifndef __TSP_HEURISTICA_OPENMPI_H
#define __TSP_HEURISTICA_OPENMPI_H                              "__TSP_HEURISTICA_OPENMPI_H"

class CTSPHeuristicaOpenMPI
{
private:
    datatest_t* m_result;

    datatokenptr_t* m_datawrk;
    datatokenptr_t** m_datares;
    long m_datasz;

    int m_appid;
    int m_nprocs;

    int m_ftype;

public:

    CTSPHeuristicaOpenMPI(
        int appid, 
        int nprocs, 
        int ftype, 
        datatest_t* result, 
        datatokenptr_t* datawrk, 
        datatokenptr_t** datares, 
        long datasz);
    ~CTSPHeuristicaOpenMPI();

    /* Methodes */

    double calculateCost(datatokenptr_t* datawrk, long size);

    void changeItemPos(long itemI, long itemF);

    void changeItemPtr(datatoken_t* pI, datatoken_t* pF);

    void copyToArray(byte* dst, datavaltest_t* resultval, datatokenptr_t* datares, long size);

    void copyFromArray(datavaltest_t* resultval, datatokenptr_t* datares, byte* src, long size);

    void copyWorkToResultData(datatokenptr_t* datawrk, datatokenptr_t* datares, long size);

    void resetResultData(datatokenptr_t* datawrk, datatokenptr_t* datares, long size);

    void execute();

    void debugData(datatokenptr_t* data, long size);

    //void debugByteArray(byte* data, long size);

};

#endif
