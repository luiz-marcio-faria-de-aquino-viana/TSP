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
 * tsp_heuristica.cpp
 */

#include"tsp_all.h"

CTSPHeuristica::CTSPHeuristica(
    int appid, 
    int nprocs, 
    int ftype, 
    datatest_t* result, 
    datatokenptr_t* datawrk, 
    datatokenptr_t* datares, 
    long datasz)
{
    m_result = result; 

    m_ftype = ftype;

    m_datawrk = datawrk;
    m_datares = datares;
    m_datasz = datasz;

    m_appid = appid;
    m_nprocs = nprocs;
}

CTSPHeuristica::~CTSPHeuristica()
{
    //TODO:
}

/* Methodes */

double CTSPHeuristica::calculateMinCost(datatokenptr_t* p1, datatokenptr_t* p2)
{
    double min_cost = DEF_MAX_VALUE;

    p2->dataptr = NULL;
    for(long i = 1; i < m_datasz; i++) 
    {
        datatokenptr_t* p_tmp = & m_datawrk[i];
        if(p_tmp->dataptr->datatoken_processed == FALSE) 
        {
            double d = calculateEuclideanDistance(m_ftype, p1->dataptr, p_tmp->dataptr);
            if(d < min_cost) {
                p2->dataptr = p_tmp->dataptr;
                min_cost = d;
            }
        }
    }

    if(p2->dataptr != NULL) {
        p2->dataptr->datatoken_processed = TRUE;
        p2->dataptr->datatoken_dist = min_cost;
        p2->datatoken_order = p2->dataptr->datatoken_order;
        p2->datatoken_dist = p2->dataptr->datatoken_dist;

        return min_cost;
    }

    return 0;
}

void CTSPHeuristica::resetResultData()
{
    for(long i = 0; i < m_datasz; i++) {
        datatokenptr_t* p_wrk = & m_datawrk[i];
        p_wrk->dataptr->datatoken_processed = FALSE;
        p_wrk->dataptr->datatoken_order = i;
        p_wrk->dataptr->datatoken_dist = 0.0;
        p_wrk->datatoken_order = i;
        p_wrk->datatoken_dist = 0.0;

        datatokenptr_t* p_dst = & m_datares[i];
        p_dst->dataptr = p_wrk->dataptr;
        p_dst->datatoken_order = i;
        p_dst->datatoken_dist = 0.0;
    }
}

void CTSPHeuristica::debugWorkData(datatokenptr_t* data, long size)
{
    printf("\n\nDEBUG: [ ");

    for(int m = 0; m < size; m++) {
        datatoken_t* pTmp = data[m].dataptr;
        printf("%ld; ", pTmp->datatoken_order);
    }

    printf(" ] ");
}

void CTSPHeuristica::execute()
{
    double ctotal = 0.0;

    resetResultData();
    
    datatokenptr_t* pI = & m_datares[0];

    datatokenptr_t* p0 = pI;
    p0->dataptr->datatoken_dist = 0.0;
    p0->datatoken_order = p0->dataptr->datatoken_order;    
    p0->datatoken_dist = p0->dataptr->datatoken_dist;
    for(int i = 1; i < m_datasz; i++) 
    {
        datatokenptr_t* p1 = & m_datares[i];
        double d = calculateMinCost(p0, p1);
        ctotal += d;

        p0 = p1;
    }

    double d = calculateEuclideanDistance(m_ftype, p0->dataptr, pI->dataptr);
    ctotal += d;

    pI->dataptr->datatoken_dist = d;
    pI->datatoken_order = pI->dataptr->datatoken_order;
    pI->datatoken_dist = pI->dataptr->datatoken_dist;

    m_result->datatest_val.datavaltest_initial_cost = ctotal; 
    m_result->datatest_val.datavaltest_final_cost = ctotal; 

}
