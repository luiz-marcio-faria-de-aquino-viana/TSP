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
 * tsp.cpp
 */

#include"tsp_all.h"

int main(int argc, char** argv)
{
    int appid = 0;
    int nprocs = 1;

#ifdef __OPENMPI__

    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, & nprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD, & appid);

    if(appid == 0) {
        gAppMain.showCabecalho();

        printf("\nMPI: MPI_ENABLE");
        printf("\n\n");

        printf("\n\nINIT...");
        
    } 

    gAppMain.init(appid, nprocs, TSP_CALC_EUCL_DIST);

    if(appid == 0) {
        printf("\n\nLOAD DATA...");
    
        gAppMain.loadData(TRUE);

    }

    char hostname[MPI_MAX_PROCESSOR_NAME];
    int hostnamesz;
    MPI_Get_processor_name(hostname, & hostnamesz);

    printf("\nRankId: %d; NProcs: %d; HostName: %s; ", appid, nprocs, hostname);
    printf("\n\n");

#ifdef __FORCABRUTA__

    if(appid == 0) 
        printf("\nTEST TSP FORCABRUTA-OPENMPI... ");

    gAppMain.testTSPForcaBrutaOpenMPI();

#endif

#ifdef __HEURISTICA__

    if(appid == 0) 
        printf("\nTEST TSP HEURISTICA-OPENMPI... ");
    
    gAppMain.testTSPHeuristicaOpenMPI();

#endif
    
    MPI_Finalize(); 

    if(appid == 0)  {
        printf("\n\nSHOW RESULTS...");
    
        gAppMain.showResults();

        printf("\n\nTERMINATE...");
    
    }

    gAppMain.terminate();
    
    if(appid == 0) {
        printf("\n\nFINISHED!");
        printf("\n\n");
    }

#else

    gAppMain.showCabecalho();

    printf("\nMPI: MPI_DISABLE");
    printf("\n\n");

    printf("\n\nINIT...");
    
    gAppMain.init(appid, nprocs, TSP_CALC_EUCL_DIST);

    printf("\n\nLOAD DATA...");
    
    gAppMain.loadData(TRUE);

    printf("\nRankId: %d; NProcs: %d; ", appid, nprocs);
    printf("\n\n");

#ifdef __FORCABRUTA__

    printf("\n\nTEST TSP-FORCABRUTA...");
    
    gAppMain.testTSPForcaBruta();

    //printf("\n\nTEST TSP-ALGO_COMPLETO...");
    
    //gAppMain.testTSPAlgoCompleto();

#endif

#ifdef __HEURISTICA__
    
    printf("\n\nTEST TSP-HEURISTICA...");
    
    gAppMain.testTSPHeuristica();

#endif

#ifdef __OPENMP__

#ifdef __FORCABRUTA__

    printf("\n\nTEST TSP-FORCABRUTA_OPENMP...");
    
    gAppMain.testTSPForcaBrutaOpenMP();
    
#endif

#ifdef __HEURISTICA__

    printf("\n\nTEST TSP-HEURISTICA_OPENMP...");

    gAppMain.testTSPHeuristicaOpenMP();

#endif

#endif

    printf("\n\nSHOW RESULTS...");
    
    gAppMain.showResults();

    printf("\n\nTERMINATE...");

    gAppMain.terminate();
    
    printf("\n\nFINISHED!");
    printf("\n\n");

#endif

    return 0;

}
