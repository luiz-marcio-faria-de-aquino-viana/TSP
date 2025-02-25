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
 * tsp_appmain.h
 */

#ifndef __TSP_APPMAIN_H
#define __TSP_APPMAIN_H                              "__TSP_APPMAIN_H"

class CTSPAppMain
{
private:
    datatest_t m_results[DEF_RESULT_NUM_TESTS];

    datatoken_t* m_data;
    long m_datasz;

    datatokenptr_t* m_datawrk[DEF_NUM_OF_THREADS];
    datatokenptr_t* m_datainv[DEF_NUM_OF_THREADS];
    datatokenptr_t* m_datares[DEF_NUM_OF_THREADS];

    int m_appid;
    int m_nprocs;

    int m_ftype;

    bigstr_t m_fileName;
    long m_fileRows;

public:

    CTSPAppMain();
    ~CTSPAppMain();

    /* Methodes */

    void showCabecalho();

    void initDataResults();
    void prepareDatasets();

    void init(int appid, int nprocs, int ftype);
    void loadData(int bShow);
    void resetData(int bShow);
    void terminate();

    void testTSPAlgoCompleto();

    void testTSPForcaBruta();
    void testTSPForcaBrutaOpenMP();
    void testTSPForcaBrutaOpenMPI();

    void testTSPHeuristica();
    void testTSPHeuristicaOpenMP();
    void testTSPHeuristicaOpenMPI();

    void showWorkData();
    void showResultData(datatokenptr_t* datares, long datasz);
    
    void showResults();

};

extern CTSPAppMain gAppMain;

#endif
