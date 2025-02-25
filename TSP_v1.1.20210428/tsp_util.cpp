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
 * tsp_util.cpp
 */

#include"tsp_all.h"

/* STRING UTILS
 */

int strIsEmptyUtil(char* src)
{
    if((*src) == '\0')
        return(TRUE);
    return(FALSE);
}

char* strSetEmptyUtil(char* src)
{
    (*src) = '\0';
    return(src);
}

char* strNExtCaseUtil(char* dst, char* src, int posI, int posF, int caseSensitive)
{
    char* p_src = & src[posI];
    char* p_dst = dst;

    int n = (posF - posI) + 1;

    int n_dst = 0;
    while(n_dst < n)
    {
        if(caseSensitive == DEF_CASESENSITIVE_TOUPPER)
            (*p_dst) = toupper(*p_src);
        else if(caseSensitive == DEF_CASESENSITIVE_TOLOWER)
            (*p_dst) = tolower(*p_src);
        else 
            (*p_dst) = (*p_src);

        if((*p_src) == '\0') break;

        p_src++;
        p_dst++;       
        n_dst += 1;
    }
    (*p_dst) = '\0';
    return(dst);
}

char* strNExtUtil(char* dst, char* src, int posI, int posF)
{
    char* p_src = & src[posI];
    char* p_dst = dst;

    int n = (posF - posI) + 1;

    int n_dst = 0;
    while(n_dst < n)
    {
        (*p_dst) = (*p_src);

        if((*p_src) == '\0') break;

        p_src++;
        p_dst++;       
        n_dst += 1;
    }
    (*p_dst) = '\0';
    return(dst);
}

char* strNCpyCaseUtil(char* dst, char* src, int n, int caseSensitive)
{
    char* p_src = src;
    char* p_dst = dst;

    int n_dst = 0;
    while(n_dst < n)
    {
        if(caseSensitive == DEF_CASESENSITIVE_TOUPPER)
            (*p_dst) = toupper(*p_src);
        else if(caseSensitive == DEF_CASESENSITIVE_TOLOWER)
            (*p_dst) = tolower(*p_src);
        else 
            (*p_dst) = (*p_src);

        if((*p_src) == '\0') break;

        p_src++;
        p_dst++;       
        n_dst += 1;
    }
    dst[n - 1] = '\0';
    return(dst);
}

char* strNCpyUtil(char* dst, char* src, int n)
{
    char* p_src = src;
    char* p_dst = dst;

    int n_dst = 0;
    while(n_dst < n)
    {
        (*p_dst) = (*p_src);

        if((*p_src) == '\0') break;

        p_src++;
        p_dst++;       
        n_dst += 1;
    }
    dst[n - 1] = '\0';
    return(dst);
}

char* strNCatUtil(char* dst, char* src, int n)
{
    char* p_src = src;
    char* p_dst = dst;

    int n_dst = 0;
    while(n_dst < n)
    {
        if((*p_dst) == '\0') break;

        p_dst++;       
        n_dst += 1;
    }

    while(n_dst < n)
    {
        (*p_dst) = (*p_src);

        if((*p_src) == '\0') break;

        p_src++;
        p_dst++;       
        n_dst += 1;
    }
    dst[n - 1] = '\0';
    return(dst);
}

int strNCmpUtil(char* src1, char* src2, int n)                                  // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2
{
    char* p_src1 = src1;
    char* p_src2 = src2;

    int n_src = 0;
    while((n_src < (n - 1)) && ((*p_src1) != '\0') && ((*p_src2) != '\0'))
    {
        if((*p_src1) < (*p_src2))
            return -1;

        if((*p_src1) > (*p_src2))
            return 1;

        p_src1++;
        p_src2++;

        n_src += 1;
    }

    if((*p_src1) < (*p_src2))
        return -1;

    if((*p_src1) > (*p_src2))
        return 1;

    return 0;
}

int strNCmpCaseUtil(char* src1, char* src2, int n, int caseSensitive)           // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2
{
    char* p_src1 = src1;
    char* p_src2 = src2;

    int n_src = 0;
    while((n_src < (n - 1)) && ((*p_src1) != '\0') && ((*p_src2) != '\0'))
    {
        int c_src1 = (*p_src1);
        int c_src2 = (*p_src2);

        if(c_src1 == DEF_CASESENSITIVE_TOUPPER) {
            c_src1 = toupper(*p_src1);
            c_src2 = toupper(*p_src2);
        }
        else if(c_src2 == DEF_CASESENSITIVE_TOLOWER) {
            c_src1 = tolower(*p_src1);
            c_src2 = tolower(*p_src2);
        }

        if(c_src1 < c_src2)
            return -1;

        if(c_src1 > c_src2)
            return 1;

        p_src1++;
        p_src2++;

        n_src += 1;
    }

    int c_src1 = (*p_src1);
    int c_src2 = (*p_src2);

    if(c_src1 == DEF_CASESENSITIVE_TOUPPER) {
        c_src1 = toupper(*p_src1);
        c_src2 = toupper(*p_src2);
    }
    else if(c_src2 == DEF_CASESENSITIVE_TOLOWER) {
        c_src1 = tolower(*p_src1);
        c_src2 = tolower(*p_src2);
    }

    if(c_src1 < c_src2)
        return -1;

    if(c_src1 > c_src2)
        return 1;

    return 0;
}

int strInStrUtil(char* src1, char* src2, int n)                                 // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2
{
    char* p_src1 = src1;
    char* p_src2 = src2;

    int bFound = FALSE;
    
    int n_src = 0;
    while((n_src < (n - 1)) && ((*p_src1) != '\0') && ((*p_src2) != '\0'))
    {
        if((*p_src1) == (*p_src2))
            bFound = TRUE;
        else
            return -1;
        p_src1++;
        p_src2++;

        n_src += 1;
    }

    if(bFound == TRUE)
        return n_src;
    return -1;
}

int strInStrCaseUtil(char* src1, char* src2, int n, int caseSensitive)          // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2
{
    char* p_src1 = src1;
    char* p_src2 = src2;

    int c_src1 = -1;
    int c_src2 = -1;

    int bFound = FALSE;
    
    int n_src = 0;
    while((n_src < (n - 1)) && ((*p_src1) != '\0') && ((*p_src2) != '\0'))
    {
        c_src1 = (*p_src1);
        c_src2 = (*p_src2);

        if(c_src1 == DEF_CASESENSITIVE_TOUPPER) {
            c_src1 = toupper(*p_src1);
            c_src2 = toupper(*p_src2);
        }
        else if(c_src2 == DEF_CASESENSITIVE_TOLOWER) {
            c_src1 = tolower(*p_src1);
            c_src2 = tolower(*p_src2);
        }

        if(c_src1 == c_src2)
            bFound = TRUE;
        else
            return -1;
        p_src1++;
        p_src2++;

        n_src += 1;
    }

    c_src1 = (*p_src1);
    c_src2 = (*p_src2);

    if(c_src1 == DEF_CASESENSITIVE_TOUPPER) {
        c_src1 = toupper(*p_src1);
        c_src2 = toupper(*p_src2);
    }
    else if(c_src2 == DEF_CASESENSITIVE_TOLOWER) {
        c_src1 = tolower(*p_src1);
        c_src2 = tolower(*p_src2);
    }

    if(c_src1 == c_src2)
        bFound = TRUE;
    else
        return -1;

    if(bFound == TRUE)
        return n_src;
    return -1;
}

char* strLTrimUtil(char* src1, int n)
{
    char* p_src = src1;
    int n_src = 0;
    while( (n_src < n) && ((*p_src) == ' ') ) {
        p_src++;
        n_src += 1;
    }
    return(p_src);
}

char* strRTrimUtil(char* src1, int n)
{
    char* p_src = src1;
    int n_src = 0;

    while( (n_src < n) && ((*p_src) != '\0') ) {
        p_src++;
        n_src += 1;
    }
    p_src--;
    n_src -= 1;

    while( (n_src >= 0) && ((*p_src) == ' ') && ((*p_src) != '\0') ) {
        p_src--;
        n_src -= 1;
    }

    return(p_src);
}

/* MEM UTILS
 */

int memIsNullUtil(byte* src, int n)
{
    for(int i = 0; i < n; i++)
    {
        if((*src) != 0)
            return(FALSE);
        src++;
    }
    return(TRUE);
}

byte* memSetNullUtil(byte* src, int n)
{
    byte* p = src;
    for(int i = 0; i < n; i++)
    {
        (*p) = 0;
        p++;
    }
    return(src);
}

byte* memNCpyUtil(byte* dst, byte* src, int n)
{
    byte* p_src = src;
    byte* p_dst = dst;

    for(int i = 0; i < n; i++)
    {
        (*p_dst) = (*p_src);

        p_src++;
        p_dst++;       
    }
    return(dst);
}

byte* memNCatUtil(byte* dst, byte* src, int n_i, int n)
{
    byte* p_src = src;
    byte* p_dst = dst;

    for(int i = 0; i < n_i; i++)
        p_dst++;       

    int n_sz = n - n_i + 1;
    for(int i = n_i; i < n_sz; i++)
    {
        (*p_dst) = (*p_src);

        p_src++;
        p_dst++;       
    }
    return(dst);
}

int memNCmpUtil(byte* src1, byte* src2, int n)      // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2
{
    byte* p_src1 = src1;
    byte* p_src2 = src2;

    for(int i = 0; i < n; i++)
    {
        if((*p_src1) < (*p_src2))
            return -1;

        if((*p_src1) > (*p_src2))
            return 1;

        p_src1++;
        p_src2++;
    }

    return 0;
}

/* PARSER DATA
 */

void initDataUtil(datatoken_t* p)
{
    p->datatoken_type = TSP_TAGID_NONE;
    p->datatoken_oid = -1;
    p->datatoken_selected = FALSE;
    p->datatoken_order = -1;
    p->datatoken_xp = 0.0;
    p->datatoken_yp = 0.0;
    p->datatoken_dist = 0.0;
}

void copyDataUtil(datatoken_t* p1, datatoken_t* p2)
{
    p1->datatoken_type = p2->datatoken_type;
    p1->datatoken_oid = p2->datatoken_oid;
    p1->datatoken_selected = p2->datatoken_selected;
    p1->datatoken_order = p2->datatoken_order;
    p1->datatoken_xp = p2->datatoken_xp;
    p1->datatoken_yp = p2->datatoken_yp;
    p1->datatoken_dist = p2->datatoken_dist;
}

void copyDataPtrUtil(datatokenptr_t* p1, datatokenptr_t* p2)
{
    p1->dataptr = p2->dataptr;
    p1->datatoken_dist = p1->dataptr->datatoken_dist;
    p1->datatoken_order = p1->dataptr->datatoken_order;
}

int parserDataUtil(datatest_t* result, datatoken_t* data, char* str)
{
    bigstr_t strTmp;
    int pos = -1;

    //printf("\n[000] Token=%s; ", str);

    pos = strInStrUtil(str, TSP_TAG_NAME, BIGSTRSZ);
    if(pos != -1) {
        strNCpyUtil(result->datatest_name, str, BIGSTRSZ);
        data->datatoken_type = TSP_TAGID_NAME;
        data->datatoken_selected = FALSE;
        return TSP_TAGID_NAME;
    }

    pos = strInStrUtil(str, TSP_TAG_COMMENT, BIGSTRSZ);
    if(pos != -1) {
        strNCpyUtil(result->datatest_comment, str, BIGSTRSZ);
        data->datatoken_type = TSP_TAGID_COMMENT;
        data->datatoken_selected = FALSE;
        return TSP_TAGID_COMMENT;
    }

    pos = strInStrUtil(str, TSP_TAG_TYPE, BIGSTRSZ);
    if(pos != -1) {
        strNCpyUtil(result->datatest_type, str, BIGSTRSZ);
        data->datatoken_type = TSP_TAGID_TYPE;
        data->datatoken_selected = FALSE;
        return TSP_TAGID_TYPE;
    }

    pos = strInStrUtil(str, TSP_TAG_DIMENSION, BIGSTRSZ);
    if(pos != -1) {
        data->datatoken_type = TSP_TAGID_DIMENSION;
        data->datatoken_selected = FALSE;
        return TSP_TAGID_DIMENSION;
    }

    pos = strInStrUtil(str, TSP_TAG_EDGE_WEIGHT_TYPE, BIGSTRSZ);
    if(pos != -1) {
        strNCpyUtil(result->datatest_edge_weight_type, str, BIGSTRSZ);
        data->datatoken_type = TSP_TAGID_EDGE_WEIGHT_TYPE;
        data->datatoken_selected = FALSE;
        return TSP_TAGID_EDGE_WEIGHT_TYPE;
    }

    pos = strInStrUtil(str, TSP_TAG_NODE_COORD_SECTION, BIGSTRSZ);
    if(pos != -1) {
        data->datatoken_type = TSP_TAGID_NODE_COORD_SECTION;
        data->datatoken_selected = FALSE;
        return TSP_TAGID_NODE_COORD_SECTION;
    }

    pos = strInStrUtil(str, TSP_TAG_EOF, BIGSTRSZ);
    if(pos != -1) {
        data->datatoken_type = TSP_TAGID_EOF;
        data->datatoken_selected = FALSE;
        return TSP_TAGID_EOF;
    }

    data->datatoken_type = TSP_TAGID_NODE_ENTRY;
    data->datatoken_selected = TRUE;
    data->datatoken_order = -1;

    strNExtUtil(strTmp, str, 0, 3);
    char* p_str1 = strLTrimUtil(strTmp, BIGSTRSZ);
    data->datatoken_oid = atol(p_str1);

    strNExtUtil(strTmp, str, 3, 7);
    p_str1 = strLTrimUtil(strTmp, BIGSTRSZ);
    data->datatoken_xp = atol(p_str1);

    strNExtUtil(strTmp, str, 7, 11);
    p_str1 = strLTrimUtil(strTmp, BIGSTRSZ);
    data->datatoken_yp = atol(p_str1);
    
    return TSP_TAGID_NODE_ENTRY;
}

void copyResultUtil(datatest_t* result, long bCopyVal)
{
    datatest_t* p0 = & result[0];
    for(int i = 1; i < DEF_RESULT_NUM_TESTS; i++)
    {
        datatest_t* p1 = & result[i];

        //strNCpyUtil(p1->datatest_title, p0->datatest_title, BIGSTRSZ);
        strNCpyUtil(p1->datatest_name, p0->datatest_name, BIGSTRSZ);
        strNCpyUtil(p1->datatest_comment, p0->datatest_comment, BIGSTRSZ);
        strNCpyUtil(p1->datatest_type, p0->datatest_type, BIGSTRSZ);
        strNCpyUtil(p1->datatest_edge_weight_type, p0->datatest_edge_weight_type, BIGSTRSZ);
        p1->datatest_val.datavaltest_dimension = p0->datatest_val.datavaltest_dimension;
        if(bCopyVal == TRUE) {
            p1->datatest_val.datavaltest_start_time = p0->datatest_val.datavaltest_start_time;
            p1->datatest_val.datavaltest_end_time = p0->datatest_val.datavaltest_end_time;
            p1->datatest_val.datavaltest_elapsed_time = p0->datatest_val.datavaltest_elapsed_time;
        }
    }
}

/* FILE OPERATIONS
 */

int existFileUtil(char* fileName)
{
    FILE* f = fopen(fileName, FILMODE_READ);
    if(f == NULL)
        return(RSERR);
    return(RSOK);
}

int openFileUtil(FILE** f, char* fileName, char* fileMode)
{
    (*f) = fopen(fileName, fileMode);
    if((*f) == NULL)
    {
        warnMsg(DEBUG_LEVEL_01, __TSP_UTIL_H, "openFile()", ERR_CANTOPENFILE);
        return(RSERR);
    }
    return(RSOK);
}

long numOfRowsFileUtil(char* fileName)
{
    bigstr_t sbuf;
    long pos = 0;

    FILE* f = fopen(fileName, "r");
    if(f != NULL) {
        char* p = fgets(sbuf, BIGSTRSZ, f);
        while( (p != NULL) && ((*p) != '\0') ) {
            pos++;
            p = fgets(sbuf, BIGSTRSZ, f);
        }
    }
    fclose(f);

    return(pos);
}

long readFileUtil(char* fileName, datatest_t* result, datatoken_t* data, long datasz)
{
    datatest_t* pResult = & result[0];
    datatoken_t* pData = data;

    bigstr_t sbuf;
    long pos = 0;

    FILE* f = fopen(fileName, "r");
    if(f != NULL)
    {
        char* p = fgets(sbuf, BIGSTRSZ, f);
        while( (p != NULL) && ((*p) != '\0') )
        {
            sbuf[BIGSTRSZ - 1] = '\0';
            sbuf[strlen(sbuf) - 1] = '\0';              // remove [ lf; cr; ]

            if(pos >= datasz)
                return pos;

            int rscode = parserDataUtil(pResult, pData, sbuf);
            if(rscode == TSP_TAGID_NODE_ENTRY) {
                pData->datatoken_order = pos;
                pData->datatoken_dist = 0.0;

                pData++;
                pos++;
            }

            p = fgets(sbuf, BIGSTRSZ, f);
        }
    }
    return pos;
}

/* ALLOC DATA OPERATIONS
 */

void* allocData(int dataSize)
{
    void* data = malloc(dataSize);
    errMsgIfNull(__TSP_UTIL_H, "allocData()", ERR_CANTALLOCATEMEMORY, data);
    return data;
}

void* allocDataArray(int dataSize, int numItens)
{
    int size = dataSize * numItens;
    void* data = malloc(size);
    errMsgIfNull(__TSP_UTIL_H, "allocDataArray()", ERR_CANTALLOCATEMEMORY, data);
    return data;
}

void freeData(void* data)
{
    if(data != NULL) free(data);
}

void freeDataArray(void* data)
{
    if(data != NULL) free(data);
}

/* HASH OPERATIONS
 */

long getHash(char* p)
{
    long hashVal = 0;

    long maxVal = 1000009;

    long q = 31;
    long q_memb = 1;

    while((*p) != '\0')
    {
        int c = (*p) - '@' + 1;

        hashVal = hashVal + ((c * q_memb) % maxVal);
        q_memb = (q_memb * q) % maxVal;
        p++;
    }
    return hashVal;
}

/* TIME OPERATIONS
 */

void getLocalTimeStr(char* local_time_str)
{
    time_t t = time(NULL);

    struct tm local_time = *localtime(&t);

    sprintf(local_time_str, 
        "%04d-%02d-%02d_%02d:%02d:%02d", 
        local_time.tm_year + 1900, 
        local_time.tm_mon + 1, 
        local_time.tm_mday, 
        local_time.tm_hour, 
        local_time.tm_min, 
        local_time.tm_sec);
}

long getCurrentTimestamp()
{
#ifdef __OPENMPI_TIME__
    double tm = (MPI_Wtime() * 1000000);
    return (long)tm;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);

    long result = (tv.tv_sec * 1000000) + tv.tv_usec;
    return result;
#endif
}

/* ENCODE/DECODE (HEX)
 */

int encodeHex(byte* in_data, long in_datasz, char** out_data, long* out_datalen)
{
    (*out_datalen) = (2 * in_datasz) + 1;
    (*out_data) = (char*)allocData( (*out_datalen) );

    byte* p_in = in_data;
    char* p_out = (*out_data);

    for(int i = 0; i < in_datasz; i++)
    {
        (*p_out) = ((*p_in) / 16) + 64;
        p_out++;

        (*p_out) = ((*p_in) % 16) + 64;
        p_out++;

        p_in++;
    }
    (*p_out) = '\0';

    return RSOK;
}

int decodeHex(char* in_data, long in_datalen, byte** out_data, long* out_datasz)
{
    long in_datasz = in_datalen - 1;

    (*out_datasz) = in_datasz / 2;
    if((in_datasz % 2) != 0)
        (*out_datasz) += 1;

    (*out_data) = (byte*)allocData( (*out_datasz) );

    char* p_in = in_data;
    byte* p_out = (*out_data);

    for(int i = 0; i < in_datasz; i += 2)
    {
        byte hb = ((*p_in) - 64) * 16;
        p_in++;

        byte lb = ((*p_in) - 64);
        p_in++;

        (*p_out) = hb + lb;
        p_out++;
    }

    return RSOK;
}
