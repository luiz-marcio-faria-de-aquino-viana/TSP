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
 * tsp_algo_completo.cpp
 */

#include"tsp_all.h"

CTSPAlgoCompleto::CTSPAlgoCompleto(
    int appid, 
    int nprocs, 
    int ftype, 
    datatest_t* result, 
    datatokenptr_t* datawrk, 
    datatokenptr_t* datainv, 
    datatokenptr_t* datares, 
    long datasz)
{
    m_result = result; 

    m_ftype = ftype;

    m_datawrk = datawrk;
    m_datainv = datainv;
    m_datares = datares;
    m_datasz = datasz;

    m_appid = appid;
    m_nprocs = nprocs;
}

CTSPAlgoCompleto::~CTSPAlgoCompleto()
{
    //TODO:
}

/* Methodes */

double CTSPAlgoCompleto::calculateCost(datatokenptr_t* datawrk, long datasz)
{
    double dist_total = 0.0;
    double d = 0.0;

    datatokenptr_t* pI = & datawrk[0];

    datatokenptr_t* p0 = pI;
    p0->dataptr->datatoken_dist = 0.0;
    p0->datatoken_dist = p0->dataptr->datatoken_dist;
    for(long i = 1; i < datasz; i++) {
        datatokenptr_t* p1 = & datawrk[i];

        d = calculateEuclideanDistance(m_ftype, p0->dataptr, p1->dataptr);
        p1->dataptr->datatoken_dist = d;
        p1->datatoken_dist = p1->dataptr->datatoken_dist;

        dist_total += d;
        p0 = p1;
    }

    d = calculateEuclideanDistance(m_ftype, p0->dataptr, pI->dataptr);
    pI->dataptr->datatoken_dist = d;
    pI->datatoken_dist = pI->dataptr->datatoken_dist;

    dist_total += d;

    return dist_total;
}

void CTSPAlgoCompleto::avaliateTotalCost(double* initial_cost, double* min_cost, datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz)
{
    double d = calculateCost(datawrk, datasz);

    //debugWorkData(datawrk, datasz);
    //getchar();

    if(d < (*min_cost)) {
        (*min_cost) = d;
        copyWorkToResultData(datares, datawrk, datasz);
    
        if((*initial_cost) < 0.05)
            (*initial_cost) = d;
    }
}

void CTSPAlgoCompleto::copyWorkToResultData(datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz)
{
    for(long i = 0; i < datasz; i++) {
        datatokenptr_t* p_wrk = & datawrk[i];        
        datatokenptr_t* p_dst = & datares[i];
        
        p_dst->dataptr = p_wrk->dataptr;
        p_dst->datatoken_order = p_dst->dataptr->datatoken_order;
        p_dst->datatoken_dist = p_dst->dataptr->datatoken_dist;
    }
}

void CTSPAlgoCompleto::resetResultData()
{
    for(long i = 0; i < m_datasz; i++) {
        datatokenptr_t* p_wrk = & m_datawrk[i];
        p_wrk->dataptr = p_wrk->initial_dataptr;
        
        p_wrk->dataptr->datatoken_processed = FALSE;
        p_wrk->dataptr->datatoken_order = i;
        p_wrk->dataptr->datatoken_dist = 0.0;

        p_wrk->datatoken_initial_order = p_wrk->dataptr->datatoken_order;
        p_wrk->datatoken_order = p_wrk->dataptr->datatoken_order;
        p_wrk->datatoken_dist = p_wrk->dataptr->datatoken_dist;

        datatokenptr_t* p_dst = & m_datares[i];
        p_dst->initial_dataptr = p_wrk->initial_dataptr;
        p_dst->dataptr = p_dst->initial_dataptr;

        p_dst->datatoken_initial_order = p_dst->dataptr->datatoken_order;
        p_dst->datatoken_order = p_dst->dataptr->datatoken_order;
        p_dst->datatoken_dist = p_dst->dataptr->datatoken_dist;
    }
}

void CTSPAlgoCompleto::changeItem(long posI, long posF, datatokenptr_t* datawrk, long datasz)
{
    datatokenptr_t* p0 = & datawrk[posI];
    datatokenptr_t* p1 = & datawrk[posF];

    datatoken_t* p_tmp = p0->dataptr;

    p0->dataptr = p1->dataptr;
    p0->dataptr->datatoken_dist = 0.0;
    p0->datatoken_step += 1;
    p0->datatoken_order = p0->dataptr->datatoken_order;
    p0->datatoken_dist = p1->dataptr->datatoken_dist;

    p1->dataptr = p_tmp;
    p1->dataptr->datatoken_dist = 0.0;
    p1->datatoken_step += 1;
    p1->datatoken_order = p1->dataptr->datatoken_order;
    p1->datatoken_dist = p1->dataptr->datatoken_dist;
}

void CTSPAlgoCompleto::execute_step1()
{
    double initial_cost = m_result->datatest_val.datavaltest_initial_cost;
    double min_cost = m_result->datatest_val.datavaltest_final_cost;

    for(long i = 1; i < m_datasz; i++) 
    {
        for(long k = 1; k < m_datasz; k++) 
        {
            if(k == i) continue; 

            for(long j = 1; j < m_datasz; j++)
            {
                if((j == i) || (j == k)) continue; 

                //printf("\ni=%ld;k=%ld;j=%ld; ", i, k, j);

                avaliateTotalCost(& initial_cost, & min_cost, m_datares, m_datawrk, m_datasz);

                changeItem(k, j, m_datawrk, m_datasz);

            }

            //printf("\ni=%ld;k=%ld; ", i, k);

            avaliateTotalCost(& initial_cost, & min_cost, m_datares, m_datawrk, m_datasz);

            changeItem(i, k, m_datawrk, m_datasz);

        }

    }

    avaliateTotalCost(& initial_cost, & min_cost, m_datares, m_datawrk, m_datasz);

    m_result->datatest_val.datavaltest_initial_cost = initial_cost;
    m_result->datatest_val.datavaltest_final_cost = min_cost;
}

void CTSPAlgoCompleto::execute_step2()
{
    double initial_cost = m_result->datatest_val.datavaltest_initial_cost;
    double min_cost = m_result->datatest_val.datavaltest_final_cost;

    for(long i = 1; i < m_datasz - 1; i++) 
    {
        for(long k = 1; k < m_datasz; k++) 
        {
            if(k == i) continue; 

            for(long j = 1; j < m_datasz; j++)
            {
                if((j == i) || (j == k)) continue; 

                //printf("\ni=%ld;k=%ld;j=%ld; ", i, k, j);

                avaliateTotalCost(& initial_cost, & min_cost, m_datares, m_datainv, m_datasz);

                changeItem(k, j, m_datainv, m_datasz);

            }

            //printf("\ni=%ld;k=%ld; ", i, k);

            avaliateTotalCost(& initial_cost, & min_cost, m_datares, m_datainv, m_datasz);

            changeItem(i, k, m_datainv, m_datasz);

        }

    }

    avaliateTotalCost(& initial_cost, & min_cost, m_datares, m_datainv, m_datasz);

    m_result->datatest_val.datavaltest_initial_cost = initial_cost;
    m_result->datatest_val.datavaltest_final_cost = min_cost;
}

void CTSPAlgoCompleto::execute()
{
    m_result->datatest_val.datavaltest_initial_cost = 0.0;
    m_result->datatest_val.datavaltest_final_cost = DEF_MAX_VALUE;

    resetResultData();

    execute_step1();
    execute_step2();
}

void CTSPAlgoCompleto::debugWorkData(datatokenptr_t* datawrk, long datasz)
{
    double ctotal = 0.0;

    printf("\n\nDEBUG: [ ");

    long size = MIN(datasz, DEF_SHOWDATA_MAX_ROWS);

    for(long i = 0; i < size; i++) {
        datatokenptr_t* p = & datawrk[i];
        printf("%ld;", p->datatoken_order);
        ctotal += p->datatoken_dist;        
    }

    printf(" ..... COST: %lf ] ", ctotal);

}
