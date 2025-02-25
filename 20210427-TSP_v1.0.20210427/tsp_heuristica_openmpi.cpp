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
    datatokenptr_t* datawrk, 
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

double CTSPHeuristicaOpenMPI::calculateCost(datatokenptr_t* datawrk, long size)
{
    double dist_total = 0.0;

    datatokenptr_t* p0 = & datawrk[0];
    p0->datatoken_dist = 0.0;
    p0->dataptr->datatoken_dist = 0.0;
    for(long i = 1; i < m_datasz; i++) {
        datatokenptr_t* p1 = & datawrk[i];
        p1->datatoken_dist = calculateEuclideanDistance(m_ftype, p0->dataptr, p1->dataptr);
        p1->dataptr->datatoken_dist = p1->datatoken_dist;
    
        dist_total += p1->datatoken_dist;
        p0 = p1;
    }
    return dist_total;
}

void CTSPHeuristicaOpenMPI::changeItemPos(long itemI, long itemF)
{
    datatoken_t* pI = m_datawrk[itemI].dataptr;
    datatoken_t* pF = m_datawrk[itemF].dataptr;

    changeItemPtr(pI, pF);
}

void CTSPHeuristicaOpenMPI::changeItemPtr(datatoken_t* pI, datatoken_t* pF)
{
    datatoken_t oTmp;

    copyDataUtil(& oTmp, pI);
    copyDataUtil(pI, pF);
    copyDataUtil(pF, & oTmp);
}

void CTSPHeuristicaOpenMPI::copyWorkToResultData(datatokenptr_t* datawrk, datatokenptr_t* datares, long size)
{
    for(long i = 0; i < size; i++) {
        datatoken_t* p = m_datawrk[i].dataptr;
        long pos = p->datatoken_order;
        
        m_datares[pos]->dataptr = p;
        m_datares[pos]->datatoken_order = pos;
        m_datares[pos]->datatoken_dist = p->datatoken_dist;

    }
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

void CTSPHeuristicaOpenMPI::resetResultData(datatokenptr_t* datawrk, datatokenptr_t* datares, long size)
{
    for(long i = 0; i < m_datasz; i++) {
        m_datawrk[i].dataptr->datatoken_order = i;
        m_datawrk[i].datatoken_order = i;
        m_datawrk[i].datatoken_dist = 0.0;
        //
        m_datares[i]->dataptr = m_datawrk[i].dataptr;
        m_datares[i]->datatoken_order = i;
        m_datares[i]->datatoken_dist = 0.0;
    }
}

// void CTSPHeuristicaOpenMPI::debugData(datatokenptr_t* data, long size)
// {
//     for(long i = 0; i < DEF_SHOWDATA_MAX_ROWS; i++) {
//         datatoken_t* p = data[i];

//         printf("\n\nDEBUG[i=%ld]: %ld;Oid=%ld;Selected=%ld;Order=%ld;Xp=%lf;Yp=%lf;Dist=%lf ",
//             i, 
//             p->datatoken_type,
//             p->datatoken_oid,
//             p->datatoken_selected,
//             p->datatoken_order,
//             p->datatoken_xp,
//             p->datatoken_yp,
//             p->datatoken_dist);
//     }
// }

// void CTSPHeuristicaOpenMPI::debugByteArray(byte* arr, long size)
// {
//     bigstr_t strTmp;
//     int strTmpSz;

//     char* p_strTmp = NULL;

//     int max_items = (size < DEF_SHOWDATA_MAX_ITEMS) ? size : DEF_SHOWDATA_MAX_ITEMS;

//     strSetEmptyUtil(strTmp);

//     byte* p = arr;
//     for(long i = 0; i < max_items; i++) {
//         p_strTmp = & strTmp[strTmpSz];
        
//         sprintf(p_strTmp, "%d;", (int)(*p));        
//         strTmpSz = strlen(strTmp);
        
//         p++;
//     }

//     printf("\n\nDEBUG_BYTEARR: Size=%ld; [ %s ]...\n\n", size, strTmp);
// }

void CTSPHeuristicaOpenMPI::execute()
{
    int numOfThreads = m_nprocs;

    int numOfWorkingThreads = numOfThreads - 1;
    int lastWorkingThreadId = (numOfWorkingThreads - 1) + 1;        // 0=MAIN THREAD / >0=WORK THREAD

    long arrsz = sizeof(datavaltest_t) + (m_datasz * sizeof(datatoken_t));
    byte arr[arrsz];

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
    MPI_Status status[numOfWorkingThreads];

    MPI_Request req_buf[numOfWorkingThreads];

    resbuf_t resbuf[numOfWorkingThreads];

    if(m_appid == 0) 
    {
        /* MAIN THREAD */

        printf("\nMain Thread %d: Started... ", m_appid);
        printf("\n\n");

        datatokenptr_t* datares = m_datares[0];
        resetResultData(m_datawrk, datares, m_datasz);

        m_result->datatest_val.datavaltest_initial_cost = 0.0;
        m_result->datatest_val.datavaltest_final_cost = 0.0;

        for(long i = 0; i < numOfWorkingThreads; i++)
        {
            long threadId = i + 1;
            long dataSize = m_datasz / numOfWorkingThreads;
            long dataStart = i * dataSize;
            
            if(threadId == lastWorkingThreadId)
                dataSize = m_datasz - dataStart;

            resbuf[i].resval[RESVAL_THREADID] = threadId;
            resbuf[i].resval[RESVAL_STARTDATA] = dataStart;
            resbuf[i].resval[RESVAL_DATASIZE] = dataSize;
        }

        int send_tag = 0;
        for(long i = 0; i < numOfWorkingThreads; i++) 
        {
            int threadId = i + 1;

            int send_to = threadId;
            MPI_Isend(& resbuf[i], NUM_RESVAL_ENTRIES, MPI_LONG, send_to, send_tag, MPI_COMM_WORLD, & req_buf[i]);
        }

        printf("\nMain Thread %d: Jobs Sent to Workers... ", m_appid);
        printf("\n\n");

        for(long i = 0; i < numOfWorkingThreads; i++)
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

            printf("\nMain Thread %d: Jobs Received from Worker [%ld]!", m_appid, threadId);
            printf("\n\n");

            copyFromArray(& m_result->datatest_val, p_datares, (byte*) arr, m_datasz);

            //debugData(p_datares, m_datasz);

        }

        printf("\nMain Thread %d: Jobs Results Received from Workers. ", m_appid);
        printf("\n\n");

    }
    else {
        /* WORK THREAD */

        printf("\nWork Thread %d: Started... ", m_appid);
        printf("\n\n");

        datatokenptr_t* datares = m_datares[m_appid];
        resetResultData(m_datawrk, datares, m_datasz);

        m_result->datatest_val.datavaltest_initial_cost = 0.0;
        m_result->datatest_val.datavaltest_final_cost = 0.0;

        int recv_from = 0;
        int recv_tag = 0;
        MPI_Recv(& resbuf[m_appid], NUM_RESVAL_ENTRIES, MPI_LONG, recv_from, recv_tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("\nWork Thread %d: Job Received... ", m_appid);
        printf("\n\n");

        //long threadId = resbuf[m_appid].resval[RESVAL_THREADID];
        long startData = resbuf[m_appid].resval[RESVAL_STARTDATA];
        long dataSize = resbuf[m_appid].resval[RESVAL_DATASIZE];

        double min_cost = DEF_MAX_VALUE;

        for(int i = 0; i < dataSize; i++) 
        {
            int pos = (startData + i);
            if(pos == 0) continue;

            int posI = 1;
            for(int j = pos; j < m_datasz; j++) 
            {
                datatoken_t* p1 = m_datawrk[posI].dataptr;
                datatoken_t* p2 = m_datawrk[j].dataptr;

                double d = calculateCost(m_datawrk, m_datasz);
                if(d < min_cost) {
                    min_cost = d;
                    copyWorkToResultData(m_datawrk, datares, m_datasz);

                    if(m_result->datatest_val.datavaltest_initial_cost < 0.05)
                        m_result->datatest_val.datavaltest_initial_cost = min_cost;
                }
                changeItemPtr(p1, p2);
                posI++;
            }
        }

        m_result->datatest_val.datavaltest_final_cost = min_cost; 

        printf("\nWork Thread %d: Sending Results... ", m_appid);
        printf("\n\n");

        byte* p_arr = arr;
        long ln_arr = arrsz;

        //debugData(datares, m_datasz);

        copyToArray((byte*) p_arr, & m_result->datatest_val, datares, m_datasz);

        int send_to = 0;
        int send_tag = m_appid;
        MPI_Send((byte*)p_arr, ln_arr, MPI_BYTE, send_to, send_tag, MPI_COMM_WORLD);

        printf("\nWork Thread %d: Job Completed. ", m_appid);
        printf("\n\n");

    }

    MPI_Barrier(MPI_COMM_WORLD);

}
