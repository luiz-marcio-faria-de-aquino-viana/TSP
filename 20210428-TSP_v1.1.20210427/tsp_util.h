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
 * tsp_util.h
 */

#ifndef __TSP_UTIL_H
#define __TSP_UTIL_H                            "__TSP_UTIL_H"

/* STRING UTILS
 */

int strIsEmptyUtil(char* src);

char* strSetEmptyUtil(char* src);

char* strNExtCaseUtil(char* dst, char* src, int posI, int posF);

char* strNExtUtil(char* dst, char* src, int posI, int posF);

char* strNCpyCaseUtil(char* dst, char* src, int n, int caseSensitive);

char* strNCpyUtil(char* dst, char* src, int n);

char* strNCatUtil(char* dst, char* src, int n);

int strNCmpUtil(char* src1, char* src2, int n);                                     // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2

int strNCmpCaseUtil(char* src1, char* src2, int n, int caseSensitive);              // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2

int strInStrUtil(char* src1, char* src2, int n);                                    // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2

int strInStrCaseUtil(char* src1, char* src2, int n, int caseSensitive);             // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2

char* strLTrimUtil(char* src1, int n);

char* strRTrimUtil(char* src1, int n);

/* MEM UTILS
 */

int memIsNullUtil(byte* src, int n);

byte* memSetNullUtil(byte* src, int n);

byte* memNCpyUtil(byte* dst, byte* src, int n);

byte* memNCatUtil(byte* dst, byte* src, int pos, int n);

int memNCmpUtil(byte* src1, byte* src2, int n);     // 0=Iguais / -1=Se src1 antecede src2 / 1=Se src1 sucede src2

/* PARSER DATA
 */

void initDataUtil(datatoken_t* p);

void copyDataUtil(datatoken_t* p1, datatoken_t* p2);

void copyDataPtrUtil(datatokenptr_t* p1, datatokenptr_t* p2);

int parserDataUtil(datatest_t* result, datatoken_t* data, char* str);

void copyResultUtil(datatest_t* result, long bCopyVal);

/* FILE OPERATIONS
 */

int existFileUtil(char* fileName);

int openFileUtil(FILE** f, char* fileName, char* fileMode);

long numOfRowsFileUtil(char* fileName);

long readFileUtil(char* fileName, datatest_t* result, datatoken_t* data, long datasz);

/* ALLOC DATA OPERATIONS
 */
 
void* allocData(int dataSize);

void* allocDataArray(int dataSize, int numItens);

void freeData(void* data);

void freeDataArray(void* data);

/* HASH OPERATIONS
 */

long getHash(char* s);

/* TIME OPERATIONS
 */

void getLocalTimeStr(char* local_time_str);

long getCurrentTimestamp();

/* ENCODE/DECODE (HEX)
 */

int encodeHex(byte* in_data, long in_datasz, char** out_data, long* out_datalen);

int decodeHex(char* in_data, long in_datalen, byte** out_data, long* out_datasz);

#endif
