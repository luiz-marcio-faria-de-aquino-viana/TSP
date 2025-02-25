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
 * tsp_appmain.cpp
 */

#include"tsp_all.h"

CTSPAppMain gAppMain;

CTSPAppMain::CTSPAppMain()
{
    strNCpyUtil(m_fileName, (char*)DEF_INPUT_FILENAME, BIGSTRSZ);
}

CTSPAppMain::~CTSPAppMain()
{
    //TODO:
}

/* Methodes */

void CTSPAppMain::showCabecalho()
{
    printf("\n=== DATA_SIZE: %ld;\nNUM_OF_THREADS: %d ===", 
        m_datasz, 
        DEF_NUM_OF_THREADS);

    printf("\n\n%s %s", 
        MOD_NAME, 
        MOD_VERSION);

    printf("\n\nPartner:\n\t%s\n\t%s", 
        MOD_PARTNER1, 
        MOD_PARTNER2);

    printf("\n\nAutor: %s", MOD_AUTHOR_NAME);
    printf("\nDRE: %s", MOD_AUTHOR_DRE);
    printf("\nCPF: %s", MOD_AUTHOR_CPF);
    printf("\nRG: %s", MOD_AUTHOR_ID);
    printf("\nPhone: %s", MOD_AUTHOR_PHONE);
    printf("\nE-mail:\n\t%s\n\t%s\n\t%s", 
        MOD_AUTHOR_EMAIL1, 
        MOD_AUTHOR_EMAIL2, 
        MOD_AUTHOR_EMAIL3);

    printf("\n\n");
}

void CTSPAppMain::initDataResults()
{
    bigstr_t tsp_title[DEF_RESULT_NUM_TESTS];

    int n = 0;
    strNCpyUtil(tsp_title[n++], (char*)"testTSPForcaBruta()", BIGSTRSZ);
    strNCpyUtil(tsp_title[n++], (char*)"testTSPForcaBrutaOpenMP()", BIGSTRSZ);
    strNCpyUtil(tsp_title[n++], (char*)"testTSPForcaBrutaOpenMPI()", BIGSTRSZ);
    strNCpyUtil(tsp_title[n++], (char*)"testTSPHeuristica()", BIGSTRSZ);
    strNCpyUtil(tsp_title[n++], (char*)"testTSPHeuristicaOpenMP()", BIGSTRSZ);
    strNCpyUtil(tsp_title[n++], (char*)"testTSPHeuristicaOpenMPI()", BIGSTRSZ);
    //strNCpyUtil(tsp_title[n++], (char*)"testTSPAlgoCompleto()", BIGSTRSZ);

    datatest_t* p = m_results;
    for(int i = 0; i < DEF_RESULT_NUM_TESTS; i++) {
        strNCpyUtil(p->datatest_title, (char*)tsp_title[i], BIGSTRSZ);
        strSetEmptyUtil(p->datatest_name);
        strSetEmptyUtil(p->datatest_comment);
        strSetEmptyUtil(p->datatest_type);
        strSetEmptyUtil(p->datatest_edge_weight_type);
        p->datatest_val.datavaltest_dimension = m_datasz;
        p->datatest_val.datavaltest_start_time = 0L;
        p->datatest_val.datavaltest_end_time = 0L;
        p->datatest_val.datavaltest_elapsed_time = 0L;
        p->datatest_val.datavaltest_initial_cost = 0.0;
        p->datatest_val.datavaltest_final_cost = 0.0;
        p++;
    }
}

void CTSPAppMain::init(int appid, int nprocs, int ftype)
{
    m_appid = appid;
    m_nprocs = nprocs;

    m_ftype = ftype;

    m_fileRows = numOfRowsFileUtil(m_fileName);
    printf("\nNumberOfFileRows: %ld", m_fileRows);

    m_datasz = m_fileRows - DEF_NUM_OF_TSPTAGS;
    m_data = (datatoken_t*)allocDataArray(sizeof(datatoken_t), (int)m_fileRows);
    
    for(int j = 0; j < DEF_NUM_OF_THREADS; j++) {
        m_datawrk[j] = (datatokenptr_t*)allocDataArray(sizeof(datatokenptr_t), (int)m_datasz);
        m_datainv[j] = (datatokenptr_t*)allocDataArray(sizeof(datatokenptr_t), (int)m_datasz);
        m_datares[j] = (datatokenptr_t*)allocDataArray(sizeof(datatokenptr_t), (int)m_datasz);
    }

    initDataResults();
}

void CTSPAppMain::prepareDatasets()
{
    long pos = 0;
    for(long i = 0; i < m_fileRows; i++)
    {
        datatoken_t* p = & m_data[i];

        if(p->datatoken_selected == TRUE) 
        {
            p->datatoken_processed = FALSE;
            p->datatoken_order = pos;

            for(int j = 0; j < DEF_NUM_OF_THREADS; j++) 
            {
                datatokenptr_t* p_wrk = & m_datawrk[j][pos];
                p_wrk->initial_dataptr = p;
                p_wrk->dataptr = p;
                p_wrk->datatoken_initial_order = p->datatoken_order;
                p_wrk->datatoken_order = p->datatoken_order;
                p_wrk->datatoken_dist = p->datatoken_dist;
                p_wrk->datatoken_step = 0;

                datatokenptr_t* p_res = & m_datares[j][pos];
                p_res->initial_dataptr = p;
                p_res->dataptr = p;
                p_res->datatoken_initial_order = p->datatoken_order;
                p_res->datatoken_order = p->datatoken_order;
                p_res->datatoken_dist = p->datatoken_dist;
                p_res->datatoken_step = 0;
            }
            pos++;
        }
    }

    for(int j = 0; j < DEF_NUM_OF_THREADS; j++) 
    {
        datatokenptr_t* p_wrk = & m_datawrk[j][0];
        datatokenptr_t* p_inv = & m_datainv[j][0];
        p_inv->initial_dataptr = p_wrk->initial_dataptr;
        p_inv->dataptr = p_wrk->dataptr;
        p_inv->datatoken_initial_order = p_inv->dataptr->datatoken_order;
        p_inv->datatoken_order = p_inv->dataptr->datatoken_order;
        p_inv->datatoken_dist = p_inv->dataptr->datatoken_dist;
        p_inv->datatoken_step = 0;

        for(long i = 1; i < pos; i++) 
        {
            long pos_inv = (pos - i);

            datatokenptr_t* p_wrk = & m_datawrk[j][pos_inv];
            datatokenptr_t* p_inv = & m_datainv[j][i];
            p_inv->initial_dataptr = p_wrk->initial_dataptr;
            p_inv->dataptr = p_wrk->dataptr;
            p_inv->datatoken_initial_order = p_inv->dataptr->datatoken_order;
            p_inv->datatoken_order = p_inv->dataptr->datatoken_order;
            p_inv->datatoken_dist = p_inv->dataptr->datatoken_dist;
            p_inv->datatoken_step = 0;
        }
    }
}

void CTSPAppMain::loadData(int bShow)
{
    readFileUtil(m_fileName, m_results, m_data, m_fileRows);
    copyResultUtil(m_results, TRUE);
    prepareDatasets();
    
    if(bShow == TRUE)
        showWorkData();
}

void CTSPAppMain::resetData(int bShow)
{
    readFileUtil(m_fileName, m_results, m_data, m_fileRows);
    copyResultUtil(m_results, FALSE);
    prepareDatasets();
    
    if(bShow == TRUE)
        showWorkData();
}

void CTSPAppMain::terminate()
{
    for(int j = 0; j < DEF_NUM_OF_THREADS; j++) {
        freeDataArray(m_datawrk[j]);
        freeDataArray(m_datainv[j]);
        freeDataArray(m_datares[j]);
    }

    freeDataArray(m_data);
    m_datasz = -1;
}

void CTSPAppMain::testTSPAlgoCompleto()
{
    datatest_t* p_results = & m_results[DEF_TSP_ALGO_COMPLETO];

    datatokenptr_t* p_datawrk = m_datawrk[0];
    datatokenptr_t* p_datainv = m_datainv[0];
    datatokenptr_t* p_datares = m_datares[0];

    resetData(FALSE);

    CTSPAlgoCompleto tspAlgoCompleto(
        m_appid, 
        m_nprocs, 
        m_ftype, 
        p_results, 
        p_datawrk, 
        p_datainv, 
        p_datares, 
        m_datasz);

    p_results->datatest_val.datavaltest_start_time = getCurrentTimestamp();

    tspAlgoCompleto.execute();

    p_results->datatest_val.datavaltest_end_time = getCurrentTimestamp();
    p_results->datatest_val.datavaltest_elapsed_time = p_results->datatest_val.datavaltest_end_time - p_results->datatest_val.datavaltest_start_time;

    if(m_appid == 0) {
        showResultData(p_datares, m_datasz);
    }

}

void CTSPAppMain::testTSPForcaBruta()
{
    datatest_t* p_results = & m_results[DEF_TSP_FORCABRUTA];

    datatokenptr_t* p_datawrk = m_datawrk[0];
    datatokenptr_t* p_datares = m_datares[0];

    resetData(FALSE);

    CTSPForcaBruta tspForcaBruta(
        m_appid, 
        m_nprocs, 
        m_ftype, 
        p_results, 
        p_datawrk, 
        p_datares, 
        m_datasz);

    p_results->datatest_val.datavaltest_start_time = getCurrentTimestamp();

    tspForcaBruta.execute();

    p_results->datatest_val.datavaltest_end_time = getCurrentTimestamp();
    p_results->datatest_val.datavaltest_elapsed_time = 
        p_results->datatest_val.datavaltest_end_time - p_results->datatest_val.datavaltest_start_time;

    if(m_appid == 0) {
        showResultData(p_datares, m_datasz);
    }

}

void CTSPAppMain::testTSPForcaBrutaOpenMP()
{
    datatest_t* p_results = & m_results[DEF_TSP_FORCABRUTA_OPENMP];

    resetData(FALSE);

    CTSPForcaBrutaOpenMP tspForcaBrutaOpenMP(
        m_appid, 
        m_nprocs, 
        m_ftype, 
        p_results, 
        m_datawrk, 
        m_datares, 
        m_datasz);

    p_results->datatest_val.datavaltest_start_time = getCurrentTimestamp();

    tspForcaBrutaOpenMP.execute();

    p_results->datatest_val.datavaltest_end_time = getCurrentTimestamp();
    p_results->datatest_val.datavaltest_elapsed_time = 
        p_results->datatest_val.datavaltest_end_time - p_results->datatest_val.datavaltest_start_time;

    if(m_appid == 0) {
        datatokenptr_t* p_datares = m_datares[0];
        showResultData(p_datares, m_datasz);
    }

}

void CTSPAppMain::testTSPForcaBrutaOpenMPI()
{
    datatest_t* p_results = & m_results[DEF_TSP_FORCABRUTA_OPENMPI];

    resetData(FALSE);

    CTSPForcaBrutaOpenMPI tspForcaBrutaOpenMPI(
        m_appid, 
        m_nprocs, 
        m_ftype, 
        p_results, 
        m_datawrk, 
        m_datares, 
        m_datasz);

    p_results->datatest_val.datavaltest_start_time = getCurrentTimestamp();

    tspForcaBrutaOpenMPI.execute();

    p_results->datatest_val.datavaltest_end_time = getCurrentTimestamp();
    p_results->datatest_val.datavaltest_elapsed_time = 
        p_results->datatest_val.datavaltest_end_time - p_results->datatest_val.datavaltest_start_time;

    if(m_appid == 0) {
        datatokenptr_t* p_datares = m_datares[0];
        showResultData(p_datares, m_datasz);
    }

}

void CTSPAppMain::testTSPHeuristica()
{
    datatest_t* p_results = & m_results[DEF_TSP_HEURISTICA];

    datatokenptr_t* p_datawrk = m_datawrk[0];
    datatokenptr_t* p_datares = m_datares[0];

    resetData(FALSE);

    CTSPHeuristica tspHeuristica(
        m_appid, 
        m_nprocs, 
        m_ftype, 
        p_results, 
        p_datawrk, 
        p_datares, 
        m_datasz);

    p_results->datatest_val.datavaltest_start_time = getCurrentTimestamp();

    tspHeuristica.execute();

    p_results->datatest_val.datavaltest_end_time = getCurrentTimestamp();
    p_results->datatest_val.datavaltest_elapsed_time = 
        p_results->datatest_val.datavaltest_end_time - p_results->datatest_val.datavaltest_start_time;

    if(m_appid == 0) {
        showResultData(p_datares, m_datasz);
    }

}

void CTSPAppMain::testTSPHeuristicaOpenMP()
{
    datatest_t* p_results = & m_results[DEF_TSP_HEURISTICA_OPENMP];

    datatokenptr_t* p_datawrk = m_datawrk[0];
    datatokenptr_t* p_datares = m_datares[0];

    resetData(FALSE);

    CTSPHeuristicaOpenMP tspHeuristicaOpenMP(
        m_appid, 
        m_nprocs, 
        m_ftype, 
        p_results, 
        p_datawrk, 
        p_datares, 
        m_datasz);

    p_results->datatest_val.datavaltest_start_time = getCurrentTimestamp();

    tspHeuristicaOpenMP.execute();

    p_results->datatest_val.datavaltest_end_time = getCurrentTimestamp();
    p_results->datatest_val.datavaltest_elapsed_time = 
        p_results->datatest_val.datavaltest_end_time - p_results->datatest_val.datavaltest_start_time;

    if(m_appid == 0) {
        showResultData(p_datares, m_datasz);
    }

}

void CTSPAppMain::testTSPHeuristicaOpenMPI()
{
    datatest_t* p_results = & m_results[DEF_TSP_HEURISTICA_OPENMPI];

    resetData(FALSE);

    CTSPHeuristicaOpenMPI tspHeuristicaOpenMPI(
        m_appid, 
        m_nprocs, 
        m_ftype, 
        p_results, 
        m_datawrk, 
        m_datares, 
        m_datasz);

    p_results->datatest_val.datavaltest_start_time = getCurrentTimestamp();

    tspHeuristicaOpenMPI.execute();

    p_results->datatest_val.datavaltest_end_time = getCurrentTimestamp();
    p_results->datatest_val.datavaltest_elapsed_time = 
        p_results->datatest_val.datavaltest_end_time - p_results->datatest_val.datavaltest_start_time;

    if(m_appid == 0) {
        datatokenptr_t* p_datares = m_datares[0];
        showResultData(p_datares, m_datasz);
    }

}

void CTSPAppMain::showWorkData()
{
    printf("\n\nENTRADA: [ ");

    long size = MIN(m_datasz, DEF_SHOWDATA_MAX_ROWS);

    for(long i = 0; i < size; i++) {
        datatokenptr_t* p = & m_datawrk[0][i];

        printf("\n\n[i=%ld]: %ld;Oid=%ld;Selected=%ld;Order=%ld;Xp=%lf;Yp=%lf;Dist=%lf ",
            i, 
            p->dataptr->datatoken_type,
            p->dataptr->datatoken_oid,
            p->dataptr->datatoken_selected,
            p->datatoken_order,
            p->dataptr->datatoken_xp,
            p->dataptr->datatoken_yp,
            p->datatoken_dist);
    }

    printf(" ..... ]\n\n");
}

void CTSPAppMain::showResultData(datatokenptr_t* datares, long datasz)
{
    printf("\n\nRESULT: [ ");

    long size = MIN(datasz, DEF_SHOWDATA_MAX_ROWS);

    for(long i = 0; i < size; i++) {
        datatokenptr_t* p = & datares[i];

        printf("\n\n[i=%ld]: %ld;Oid=%ld;Selected=%ld;Order=%ld;Xp=%lf;Yp=%lf;Dist=%lf ",
            i, 
            p->dataptr->datatoken_type,
            p->dataptr->datatoken_oid,
            p->dataptr->datatoken_selected,
            p->datatoken_order,
            p->dataptr->datatoken_xp,
            p->dataptr->datatoken_yp,
            p->datatoken_dist);        
    }

    printf(" ..... ] ");

}

void CTSPAppMain::showResults()
{
    printf("\n\nFINAL RESULT: ");

    for(int i = 0; i < DEF_RESULT_NUM_TESTS; i++) {
        datatest_t* p = & m_results[i];

        if(p->datatest_val.datavaltest_initial_cost <= 0.05) continue;

        printf("\n\n[%d] %s",
            i,
            p->datatest_title); 

        printf("\nName=%s;Comment=%s;Type=%s;EdgeWeightType=%s;Dimension=%ld;Start=%ld;End=%ld;Dif=%ld;ICost=%lf;FCost=%lf ", 
            p->datatest_name,
            p->datatest_comment,
            p->datatest_type,
            p->datatest_edge_weight_type,
            p->datatest_val.datavaltest_dimension,
            p->datatest_val.datavaltest_start_time,
            p->datatest_val.datavaltest_end_time,
            p->datatest_val.datavaltest_elapsed_time,
            p->datatest_val.datavaltest_initial_cost,
            p->datatest_val.datavaltest_final_cost);
    }
    printf("\n\n");
}
