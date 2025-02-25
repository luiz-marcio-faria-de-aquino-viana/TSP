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
 * tsp_error.cpp
 */

#include"tsp_all.h"

void warnMsg(int debugLevel, const char* className, const char* methodName, const char* errorMessage)
{
    if(debugLevel != DEBUG_LEVEL) return;

    //bigstr_t local_time_str;
    //getLocalTimeStr(local_time_str);
    //printf("%s WARN(%s_%s): %s\n", local_time_str, className, methodName, errorMessage);

    printf("WARN(%s_%s): %s\n", className, methodName, errorMessage);
}

void warnMsgIfNull(int debugLevel, const char* className, const char* methodName, const char* errorMessage, void* data)
{
    if(debugLevel != DEBUG_LEVEL) return;

    if(data == NULL) {
        warnMsg(debugLevel, className, methodName, errorMessage);
    }
}

void errMsg(const char* className, const char* methodName, const char* errorMessage)
{
    //bigstr_t local_time_str;
    //getLocalTimeStr(local_time_str);
    //printf("%s ERR(%s_%s): %s\n", local_time_str, className, methodName, errorMessage);
 
    printf("ERR(%s_%s): %s\n", className, methodName, errorMessage);
    exit(1);
}

void errMsgIfNull(const char* className, const char* methodName, const char* errorMessage, void* data)
{
    if(data == NULL) {
        errMsg(className, methodName, errorMessage);
    }
}
