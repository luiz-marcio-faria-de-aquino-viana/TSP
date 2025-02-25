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
 * tsp_heuristica_openmpi.cpp
 */

#include"tsp_all.h"

CTSPHeuristicaOpenMPI::CTSPHeuristicaOpenMPI(
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

CTSPHeuristicaOpenMPI::~CTSPHeuristicaOpenMPI()
{
    //TODO:
}

/* Methodes */

long CTSPHeuristicaOpenMPI::findItemAt(long currpos, long* tidStartData)
{
    for(long j = 1; j < DEF_NUM_OF_THREADS; j++)
    {
        long pos0 = tidStartData[j] - 1;
        long pos1 = tidStartData[j];
        if((currpos == pos0) || (currpos == pos1))
            return TRUE;
    }
    return FALSE;
}

double CTSPHeuristicaOpenMPI::calculateMinCost(datatokenptr_t* p1, datatokenptr_t* p2, datatokenptr_t* datawrk, long datasz, long* tidStartData)
{
    double min_cost = DEF_MAX_VALUE;

    p2->dataptr = NULL;
    for(long i = 1; i < datasz; i++) 
    {
        long bFound = findItemAt(i, tidStartData);
        if(bFound == TRUE) {
            p2->dataptr = p2->initial_dataptr;
            
            double d = calculateEuclideanDistance(m_ftype, p1->dataptr, p2->initial_dataptr);
            if(d < min_cost)
                min_cost = d;
        }
        else {
            datatokenptr_t* p_tmp = & datawrk[i];
            if(p_tmp->dataptr->datatoken_processed == FALSE) 
            {
                double d = calculateEuclideanDistance(m_ftype, p1->dataptr, p_tmp->initial_dataptr);
                if(d < min_cost) {
                    p2->dataptr = p_tmp->initial_dataptr;
                    min_cost = d;
                }
            }
        }
    }

    if(p2->dataptr != NULL) {
        p2->dataptr->datatoken_processed = TRUE;
        p2->datatoken_dist = min_cost;
        
        return min_cost;
    }

    return 0;
}

double CTSPHeuristicaOpenMPI::calculateTotalCost(datatokenptr_t* data, long datasz)
{
    datatokenptr_t* p0;
    datatokenptr_t* p1;

    double ctotal, d;
    long k;
    
    ctotal = 0.0;

    p0 = & data[0];
    p0->datatoken_dist = 0.0;
    for(k = 1; k < datasz; k++) 
    {
        p1 = & data[k];

        d = calculateEuclideanDistance(m_ftype, p0->dataptr, p1->dataptr);
        p1->datatoken_dist = d;
        ctotal += d;

        p0 = p1;
    }

    p1 = & data[0];

    d = calculateEuclideanDistance(m_ftype, p0->dataptr, p1->dataptr);
    p1->datatoken_dist = d;
    ctotal += d;

    return ctotal;
}

void CTSPHeuristicaOpenMPI::copyToArray(byte* dst, datavaltest_t* resultval, datatokenptr_t* datares, long size)
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

void CTSPHeuristicaOpenMPI::copyFromArray(datavaltest_t* resultval, datatokenptr_t* datares, byte* src, long size)
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

void CTSPHeuristicaOpenMPI::mergeResultData(datatokenptr_t* p_dst, datatokenptr_t* p_src, long datasz)
{    
    for(long i = 0; i < datasz; i++) {
        p_dst[i].dataptr = p_src[i].dataptr;
        p_dst[i].datatoken_order = p_src[i].datatoken_order;
        p_dst[i].datatoken_dist = p_src[i].datatoken_dist;
    }
}

void CTSPHeuristicaOpenMPI::resetResultData(datatokenptr_t* datares, datatokenptr_t* datawrk, long datasz)
{
    for(long i = 0; i < datasz; i++) {
        datatokenptr_t* p_wrk = & datawrk[i];
        p_wrk->dataptr->datatoken_processed = FALSE;
        p_wrk->dataptr->datatoken_order = i;
        p_wrk->dataptr->datatoken_dist = 0.0;
        p_wrk->datatoken_order = i;
        p_wrk->datatoken_dist = 0.0;

        datatokenptr_t* p_dst = & datares[i];
        p_dst->dataptr = p_wrk->dataptr;
        p_dst->datatoken_order = i;
        p_dst->datatoken_dist = 0.0;
    }
}

void CTSPHeuristicaOpenMPI::debugWorkData(datatokenptr_t* data, long size)
{
    printf("\n\nDEBUG: [ ");

    for(int m = 0; m < size; m++) {
        datatoken_t* pTmp = data[m].dataptr;
        printf("%ld; ", pTmp->datatoken_order);
    }

    printf(" ] ");
}

void CTSPHeuristicaOpenMPI::execute()
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

    datatokenptr_t* p0;
    datatokenptr_t* p1;

    long pos0, pos1;
    long i;

    double ctotal;

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
            long tidDataSz = ((datasz - 1) / nThreads);
            long tidStartData = tid * tidDataSz;

            if(tid == (nThreads - 1))
                tidDataSz = (datasz - 1) - tidStartData;

            /* Create Tasks Result Buffer */

            long threadId = i + 1;
            resbuf[i].resval[RESVAL_THREADID] = threadId;
            resbuf[i].resval[RESVAL_STARTDATA] = tidStartData;
            resbuf[i].resval[RESVAL_DATASIZE] = tidDataSz;
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

        long tidDataSz = ((datasz - 1) / nThreads);
        long tidStartData = 0;

        if(tid == (nThreads - 1))
            tidDataSz = (datasz - 1) - tidStartData;

        pos0 = tidStartData;

        p0 = & curr_datares[pos0];
        p0->datatoken_dist = 0.0;
        for(i = 1; i < tidDataSz; i++) 
        {
            pos1 = tidStartData + i;

            p1 = & curr_datares[pos1];
            p1->datatoken_dist = 0.0;

            calculateMinCost(p0, p1, curr_datawrk, datasz, & tidStartData);
            p0 = p1;
        }

        ctotal = calculateTotalCost(curr_datawrk, datasz);
        
        initial_cost[tid] = ctotal;
        final_cost[tid] = ctotal;

        printf("\nMain Thread %d: Data Processed: InitCost=%lf; FinalCost=%lf; ", tid, initial_cost[tid], final_cost[tid]);
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

        initial_cost[tid] = 0.0;
        final_cost[tid] = 0.0;

        long tidDataSz = resbuf[tid].resval[RESVAL_DATASIZE];
        long tidStartData = resbuf[tid].resval[RESVAL_STARTDATA];

        if(tid == (nThreads - 1))
            tidDataSz = (datasz - 1) - tidStartData;

        pos0 = tidStartData;

        p0 = & curr_datares[pos0];
        p0->datatoken_dist = 0.0;
        for(i = 1; i < tidDataSz; i++) 
        {
            pos1 = tidStartData + i;

            p1 = & curr_datares[pos1];
            p1->datatoken_dist = 0.0;

            calculateMinCost(p0, p1, curr_datawrk, datasz, & tidStartData);
            p0 = p1;
        }

        ctotal = calculateTotalCost(curr_datawrk, datasz);
        
        initial_cost[tid] = ctotal;
        final_cost[tid] = ctotal;

        printf("\nWork Thread %d: Data Processed: InitCost=%lf; FinalCost=%lf; ", tid, initial_cost[tid], final_cost[tid]);
        printf("\n\n");

        m_result->datatest_val.datavaltest_initial_cost = initial_cost[tid]; 
        m_result->datatest_val.datavaltest_final_cost = final_cost[tid]; 

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
