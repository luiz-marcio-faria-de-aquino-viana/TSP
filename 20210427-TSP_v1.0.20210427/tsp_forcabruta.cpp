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
 * tsp_forcabruta.cpp
 */

#include"tsp_all.h"

CTSPForcaBruta::CTSPForcaBruta(
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

CTSPForcaBruta::~CTSPForcaBruta()
{
    //TODO:
}

/* Methodes */

double CTSPForcaBruta::calculateCost(datatokenptr_t* datawrk, long datasz)
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

void CTSPForcaBruta::avaliateTotalCost(double* initial_cost, double* min_cost, datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz)
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

void CTSPForcaBruta::copyWorkToResultData(datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz)
{
    for(long i = 0; i < datasz; i++) {
        datatokenptr_t* p_wrk = & datawrk[i];        
        datatokenptr_t* p_dst = & datares[i];
        
        p_dst->dataptr = p_wrk->dataptr;
        p_dst->datatoken_order = p_dst->dataptr->datatoken_order;
        p_dst->datatoken_dist = p_dst->dataptr->datatoken_dist;
    }
}

void CTSPForcaBruta::resetResultData()
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

long CTSPForcaBruta::validData(datatokenptr_t* datawrk, long datasz)
{
    for(long i = 0; i < datasz - 1; i++) {
        datatokenptr_t* p1 = & datawrk[i];
        long pos2 = p1->datatoken_order;

        datatokenptr_t* p2 = & datawrk[pos2];
        p1->dataptr = p2->initial_dataptr;

        for(long j = i + 1; j < datasz; j++) {
            datatokenptr_t* p_tmp = & datawrk[j];
            if(p1->datatoken_order == p_tmp->datatoken_order)
                return FALSE;
        }
    }

    datatokenptr_t* p1 = & datawrk[datasz - 1];
    long pos2 = p1->datatoken_order;

    datatokenptr_t* p2 = & datawrk[pos2];
    p1->dataptr = p2->initial_dataptr;

    return TRUE;
}

long CTSPForcaBruta::executeStep(datatokenptr_t* datawrk, long datasz)
{
    long isRunning = TRUE;

    long max_val = datasz - 1;
    long last_pos = datasz - 1;

    for(long i = 1; i < datasz; i++)
    {
        datatokenptr_t* p1 = & datawrk[i];

        long initial_order1 = p1->datatoken_initial_order;
        long new_step1 = p1->datatoken_step + 1;
        if(new_step1 <= max_val) {
            long new_order1 = (initial_order1 + new_step1) % (max_val + 1);

            p1->datatoken_step = new_step1;
            p1->datatoken_order = new_order1;

            break;
        }
        else {
            new_step1 = 0;
            long new_order1 = (initial_order1 + new_step1) % (max_val + 1);

            p1->datatoken_step = new_step1;
            p1->datatoken_order = new_order1;

            if(i == last_pos) {
                isRunning = FALSE;
                break;
            }
        }
    }

    return isRunning;
}

void CTSPForcaBruta::execute()
{
    double min_cost = DEF_MAX_VALUE;
    double initial_cost = 0.0;

    resetResultData();

    long isRunning = TRUE;
    while(isRunning == TRUE) 
    {
        long bIsValid = validData(m_datawrk, m_datasz);
        if(bIsValid == TRUE) {
            avaliateTotalCost(& initial_cost, & min_cost, m_datares, m_datawrk, m_datasz);
        }
        isRunning = executeStep(m_datawrk, m_datasz);
    }

    m_result->datatest_val.datavaltest_initial_cost = initial_cost;
    m_result->datatest_val.datavaltest_final_cost = min_cost;
}

void CTSPForcaBruta::debugWorkData(datatokenptr_t* datawrk, long datasz)
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
