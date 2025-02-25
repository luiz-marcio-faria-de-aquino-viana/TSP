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
 * tsp_forcabruta_openmpi.cpp
 */

#include"tsp_all.h"

CTSPForcaBrutaOpenMPI::CTSPForcaBrutaOpenMPI(
    int appid, 
    int nprocs, 
    int ftype, 
    datatest_t* result, 
    datatokenptr_t** datawrk, 
    datatokenptr_t** datares, 
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

CTSPForcaBrutaOpenMPI::~CTSPForcaBrutaOpenMPI()
{
    //TODO:
}

/* Methodes */

double CTSPForcaBrutaOpenMPI::calculateCost(datatokenptr_t* datawrk, long datasz)
{
    double dist_total = 0.0;
    double d = 0.0;

    datatokenptr_t* pI = & datawrk[0];

    datatokenptr_t* p0 = pI;
    p0->datatoken_dist = 0;
    for(long i = 1; i < datasz; i++) {
        datatokenptr_t* p1 = & datawrk[i];

        d = calculateEuclideanDistance(m_ftype, p0->dataptr, p1->dataptr);
        dist_total += d;

        p1->datatoken_dist = d;

        p0 = p1;
    }

    d = calculateEuclideanDistance(m_ftype, p0->dataptr, pI->dataptr);
    dist_total += d;

    pI->datatoken_dist = d;

    return dist_total;
}

void CTSPForcaBrutaOpenMPI::avaliateTotalCost(int tid, double* initial_cost, double* min_cost, datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz)
{
    double d = calculateCost(datawrk, datasz);

    //debugWorkData(tid, datawrk, datasz);
    //getchar();

    if(d < (*min_cost)) {
        (*min_cost) = d;
        copyWorkToResultData(datares, datawrk, datasz);
    
        if((*initial_cost) < 0.05)
            (*initial_cost) = d;
    }
}

void CTSPForcaBrutaOpenMPI::copyWorkToResultData(datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz)
{
    for(long i = 0; i < datasz; i++) {
        datatokenptr_t* p_wrk = & datawrk[i];        
        datatokenptr_t* p_dst = & datares[i];
        
        p_dst->dataptr = p_wrk->dataptr;
        p_dst->datatoken_order = p_wrk->datatoken_order;
        p_dst->datatoken_dist = p_wrk->datatoken_dist;
    }
}

void CTSPForcaBrutaOpenMPI::copyToArray(byte* dst, datavaltest_t* resultval, datatokenptr_t* datares, long size)
{
    datatoken_t oTmp;
    byte* p_dst = dst;

    memNCpyUtil(p_dst, (byte*)resultval, sizeof(datavaltest_t));
    p_dst += sizeof(datavaltest_t);

    for(long i = 0; i < size; i++) {
        datatoken_t* p_src = datares[i].dataptr;

        oTmp.datatoken_type = p_src->datatoken_type;
        oTmp.datatoken_oid = p_src->datatoken_oid;
        oTmp.datatoken_selected = p_src->datatoken_selected;
        oTmp.datatoken_order = p_src->datatoken_order;
        oTmp.datatoken_xp = p_src->datatoken_xp;
        oTmp.datatoken_yp = p_src->datatoken_yp;
        oTmp.datatoken_dist = p_src->datatoken_dist;

        memNCpyUtil(p_dst, (byte*) &oTmp, sizeof(datatoken_t));
        p_dst += sizeof(datatoken_t);
    }
}

void CTSPForcaBrutaOpenMPI::copyFromArray(datavaltest_t* resultval, datatokenptr_t* datares, byte* src, long size)
{
    byte* p_src = src;

    memNCpyUtil((byte*)resultval, src, sizeof(datavaltest_t));
    p_src += sizeof(datavaltest_t);

    datatoken_t* p_srcdata = (datatoken_t*)p_src;
    for(long i = 0; i < size; i++) {
        datatoken_t* p_dst = datares[i].dataptr;

        p_dst->datatoken_type = p_srcdata->datatoken_type;
        p_dst->datatoken_oid = p_srcdata->datatoken_oid;
        p_dst->datatoken_selected = p_srcdata->datatoken_selected;
        p_dst->datatoken_order = p_srcdata->datatoken_order;
        p_dst->datatoken_xp = p_srcdata->datatoken_xp;
        p_dst->datatoken_yp = p_srcdata->datatoken_yp;
        p_dst->datatoken_dist = p_srcdata->datatoken_dist;

        p_srcdata++;
    }

}

void CTSPForcaBrutaOpenMPI::mergeResultData(datatokenptr_t* p_dst, datatokenptr_t* p_src, long datasz)
{    
    for(long i = 0; i < datasz; i++) {
        p_dst[i].dataptr = p_src[i].dataptr;
        p_dst[i].datatoken_order = p_src[i].datatoken_order;
        p_dst[i].datatoken_dist = p_src[i].datatoken_dist;
    }
}

void CTSPForcaBrutaOpenMPI::resetResultData(datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz)
{
    for(long i = 0; i < datasz; i++) {
        datatokenptr_t* p_wrk = & datawrk[i];
        p_wrk->datatoken_initial_order = i;
        p_wrk->datatoken_order = i;
        p_wrk->datatoken_dist = 0.0;

        p_wrk->dataptr = p_wrk->initial_dataptr;        
        p_wrk->dataptr->datatoken_processed = FALSE;
        p_wrk->dataptr->datatoken_order = i;
        p_wrk->dataptr->datatoken_dist = 0.0;

        datatokenptr_t* p_dst = & datares[i];
        p_dst->datatoken_initial_order = i;
        p_dst->datatoken_order = i;
        p_dst->datatoken_dist = 0.0;

        p_dst->initial_dataptr = p_wrk->initial_dataptr;
        p_dst->dataptr = p_dst->initial_dataptr;
    }
}

long CTSPForcaBrutaOpenMPI::validData(datatokenptr_t* datawrk, long datasz)
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

long CTSPForcaBrutaOpenMPI::executeStep(long inival, long finval, datatokenptr_t* datawrk, long datasz)
{
    long isRunning = TRUE;

    long max_val = datasz - 1;
    long last_pos = datasz - 1;

    for(long i = 1; i < datasz; i++)
    {
        datatokenptr_t* p1 = & datawrk[i];

        long initial_order1 = p1->datatoken_initial_order;

        long new_step1 = p1->datatoken_step + 1;
        if((i == 1) && (new_step1 < inival)) 
            new_step1 = inival;

        if(new_step1 <= finval) {
            long new_order1 = (initial_order1 + new_step1) % (max_val + 1);

            p1->datatoken_step = new_step1;
            p1->datatoken_order = new_order1;

            break;
        }
        else {
            new_step1 = (i == 1) ? inival : 0;

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

void CTSPForcaBrutaOpenMPI::execute()
{
    int nThreads = m_nprocs;                                // 0=MAIN THREAD / >0=WORK THREAD
    int tid = m_appid;

    int nWorkThreads = nThreads - 1;

    long arrsz = sizeof(datavaltest_t) + (m_datasz * sizeof(datatoken_t));
    byte arr[arrsz];

    double initial_cost[DEF_NUM_OF_THREADS];
    double final_cost[DEF_NUM_OF_THREADS];

    datatokenptr_t* curr_datares = m_datares[tid];
    datatokenptr_t* curr_datawrk = m_datawrk[tid];
    long datasz = m_datasz;

    double inicost = 0.0;
    double fincost = DEF_MAX_VALUE;

    resetResultData(curr_datares, curr_datawrk, datasz);

    // MPI_Status
    //
    // pub struct ompi_status_public_t {
    //   source: int,
    //   tag: int,
    //   err: int,
    //   cancelled: int,
    //   count: size_t
    // }
    //
    MPI_Status status[nWorkThreads];

    MPI_Request req_buf[nWorkThreads];

    resbuf_t resbuf[nWorkThreads];

    if(tid == 0) 
    {
        /* MAIN THREAD */

        printf("\nMain Thread %d: Started... ", tid);
        printf("\n\n");

        m_result->datatest_val.datavaltest_initial_cost = 0.0;
        m_result->datatest_val.datavaltest_final_cost = 0.0;

        for(long i = 0; i < nWorkThreads; i++)
        {
            long tidLenVal = ((datasz - 1) / nThreads);
            long tidStartVal = tid * tidLenVal;

            if(tid == (nThreads - 1))
                tidLenVal = (datasz - 1) - tidStartVal;

            /* Create Tasks Result Buffer */

            long threadId = i + 1;
            resbuf[i].resval[RESVAL_THREADID] = threadId;
            resbuf[i].resval[RESVAL_STARTDATA] = tidStartVal;
            resbuf[i].resval[RESVAL_DATASIZE] = tidLenVal;
        }

        int send_tag = 0;
        for(long i = 0; i < nWorkThreads; i++) 
        {
            int threadId = i + 1;

            int send_to = threadId;
            MPI_Isend(& resbuf[i], NUM_RESVAL_ENTRIES, MPI_LONG, send_to, send_tag, MPI_COMM_WORLD, & req_buf[i]);
        }

        printf("\nMain Thread %d: Jobs Sent to Workers... ", tid);
        printf("\n\n");

        /* Main Thread Data Processing */

        printf("\nMain Thread %d: Starting Data Processing... ", tid);
        printf("\n\n");

        initial_cost[tid] = 0.0;
        final_cost[tid] = 0.0;

        long tidLenVal = ((datasz - 1) / nThreads);
        long tidStartVal = 0;

        if(tid == (nThreads - 1))
            tidLenVal = (datasz - 1) - tidStartVal;

        long inival = tidStartVal;
        long finval = (tidStartVal + tidLenVal);

        long isRunning = TRUE;
        while(isRunning == TRUE) 
        {
            long bIsValid = validData(curr_datawrk, datasz);
            if(bIsValid == TRUE) {
                avaliateTotalCost(tid, & inicost, & fincost, curr_datares, curr_datawrk, datasz);
            }
            isRunning = executeStep(inival, finval, curr_datawrk, datasz);
        }

        initial_cost[tid] = inicost;
        final_cost[tid] = fincost;

        printf("\nMain Thread %d: Data Processed: InitCost=%lf; FinalCost=%lf; ", tid, inicost, fincost);
        printf("\n\n");

        m_result->datatest_val.datavaltest_initial_cost = initial_cost[tid]; 
        m_result->datatest_val.datavaltest_final_cost = final_cost[tid]; 

        /* Main Thread Receiving Results */

        printf("\nMain Thread %d: Receiving Results... ", tid);
        printf("\n\n");

        for(long i = 0; i < nWorkThreads; i++)
        {
            long threadId = i + 1;

            datatokenptr_t* p_datares = m_datares[threadId];

            int recv_from = threadId;
            int recv_tag = threadId;

            byte* p_arr = arr;
            long ln_arr = arrsz;

            memSetNullUtil(p_arr, (int)ln_arr);
            MPI_Recv(p_arr, ln_arr, MPI_BYTE, recv_from, recv_tag, MPI_COMM_WORLD, & status[i]);

            int num_read = 0;
            if(status[i].MPI_ERROR ==  MPI_ERR_TRUNCATE) 
            {
                while(status[i].MPI_ERROR ==  MPI_ERR_TRUNCATE) 
                {
                    MPI_Get_count(& status[i], MPI_BYTE, & num_read);
                    if(num_read <= 0) break;
                    
                    ln_arr = ln_arr - num_read;
                    if(ln_arr > 0) {
                        p_arr += num_read;              
    
                        memSetNullUtil(p_arr, (int)ln_arr);
                        MPI_Recv(p_arr, ln_arr, MPI_BYTE, recv_from, recv_tag, MPI_COMM_WORLD, & status[i]);
                    }
                }
            }

            printf("\nMain Thread %d: Jobs Received from Worker [%ld]!", tid, threadId);
            printf("\n\n");

            datatest_t results;
            copyFromArray(& results.datatest_val, p_datares, (byte*) arr, datasz);

            initial_cost[threadId] = inicost;
            final_cost[threadId] = fincost;

            //debugData(p_datares, m_datasz);

        }

        printf("\nMain Thread %d: Jobs Results Received from Workers. ", tid);
        printf("\n\n");

        /* Merge Results */

        datatokenptr_t* p_dst = m_datares[0];

        datavaltest_t* p_tst = & m_result->datatest_val;
        for(int i = 1; i < DEF_NUM_OF_THREADS; i++) 
        {
            if(final_cost[i] < p_tst->datavaltest_final_cost) 
            {
                p_tst->datavaltest_final_cost = final_cost[i];
        
                datatokenptr_t* p_src = m_datares[i];
                mergeResultData(p_dst, p_src, m_datasz);
            }
        }

    }
    else {
        /* WORK THREAD */

        printf("\nWork Thread %d: Started... ", tid);
        printf("\n\n");

        m_result->datatest_val.datavaltest_initial_cost = 0.0;
        m_result->datatest_val.datavaltest_final_cost = 0.0;

        int recv_from = 0;
        int recv_tag = 0;
        MPI_Recv(& resbuf[tid], NUM_RESVAL_ENTRIES, MPI_LONG, recv_from, recv_tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("\nWork Thread %d: Job Received... ", tid);
        printf("\n\n");

        long tidLenVal = resbuf[tid].resval[RESVAL_DATASIZE];
        long tidStartVal = resbuf[tid].resval[RESVAL_STARTDATA];

        long inival = tidStartVal;
        long finval = (tidStartVal + tidLenVal);

        long isRunning = TRUE;
        while(isRunning == TRUE) 
        {
            long bIsValid = validData(curr_datawrk, datasz);
            if(bIsValid == TRUE) {
                avaliateTotalCost(tid, & inicost, & fincost, curr_datares, curr_datawrk, datasz);
            }
            isRunning = executeStep(inival, finval, curr_datawrk, datasz);
        }

        initial_cost[tid] = inicost;
        final_cost[tid] = fincost;

        printf("\nWork Thread %d: Job Finished. ", tid);
        printf("\n\n");

        /* Merge Results */

        printf("\nWork Thread %d: Sending Job Results... ", tid);
        printf("\n\n");

        m_result->datatest_val.datavaltest_initial_cost = initial_cost[tid]; 
        m_result->datatest_val.datavaltest_final_cost = final_cost[tid]; 

        byte* p_arr = arr;
        long ln_arr = arrsz;

        //debugData(datares, m_datasz);

        copyToArray((byte*) p_arr, & m_result->datatest_val, curr_datares, datasz);

        int send_to = 0;
        int send_tag = tid;
        MPI_Send((byte*) p_arr, ln_arr, MPI_BYTE, send_to, send_tag, MPI_COMM_WORLD);

        printf("\nWork Thread %d: Job Completed. ", tid);
        printf("\n\n");

    }

    MPI_Barrier(MPI_COMM_WORLD);

}

void CTSPForcaBrutaOpenMPI::debugWorkData(int tid, datatokenptr_t* datawrk, long datasz)
{
    double ctotal = 0.0;

    printf("\n\nDEBUG[TID=%d]: [ ", tid);

    long size = MIN(datasz, DEF_SHOWDATA_MAX_ROWS);

    for(long i = 0; i < size; i++) {
        datatokenptr_t* p = & datawrk[i];
        printf("%ld;", p->datatoken_order);
        ctotal += p->datatoken_dist;        
    }

    printf(" ..... ");

    for(long i = 0; i < size; i++) {
        datatokenptr_t* p = & datawrk[i];
        printf("%ld;", p->datatoken_step);
        ctotal += p->datatoken_dist;        
    }

    printf(" ..... COST: %lf ] ", ctotal);

}
