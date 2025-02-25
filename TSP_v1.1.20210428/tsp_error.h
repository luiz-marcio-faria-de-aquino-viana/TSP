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
 * tsp_error.h
 */

#ifndef __TSP_ERROR_H
#define __TSP_ERROR_H                           "__TSP_ERROR_H"

/* ERROR MESSAGES
 */
#define ERR_CANTALLOCATEMEMORY                  "Can't allocate memory"
#define ERR_FILENOTFOUND                        "File not found"
#define ERR_CANTOPENFILE                        "Can't open file"

/* ERROR FUNCTIONS
 */

void warnMsg(int debugLevel, const char* className, const char* methodName, const char* errorMessage);

void warnMsgIfNull(int debugLevel, const char* className, const char* methodName, const char* errorMessage, void* data);

void errMsg(const char* className, const char* methodName, const char* errorMessage);

void errMsgIfNull(const char* className, const char* methodName, const char* errorMessage, void* data);

#endif
