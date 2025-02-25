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
 * tsp_defs.h
 */

//1920 thread ripple
// - QUEM FAZ O TRABALHO SUJO

#ifndef __TSP_DEFS_H
#define __TSP_DEFS_H                            "__TSP_DEFS_H"

#define __OPENMP__                              "__OPENMP__"
//#define __OPENMPI__                             "__OPENMPI__"
//#define __OPENMPI_TIME__                      "__OPENMPI_TIME__"

#define DEBUG_LEVEL_00                          0
#define DEBUG_LEVEL_01                          1
#define DEBUG_LEVEL_02                          2
#define DEBUG_LEVEL_03                          3
#define DEBUG_LEVEL_04                          4
//
#define DEBUG_LEVEL_99                          99

#define DEBUG_LEVEL                             1

#define MPI_DISABLE                             0
#define MPI_ENABLE                              1

/* DEFINITIONS
 */
#define MOD_NAME                                ((char*)"TSP - SYMMETRIC TRAVELING SALESMAN")

#define MOD_VERSION                             ((char*)"v1.0.20210427")

#define MOD_PARTNER1                            ((char*)"COPPE/UFRJ - Universidade Federal do Rio de Janeiro")
#define MOD_PARTNER2                            ((char*)"TLMV Consultoria e Sistemas EIRELI")

#define MOD_AUTHOR_NAME                         ((char*)"Luiz Marcio Faria de Aquino Viana, M.Sc.")
#define MOD_AUTHOR_DRE                          ((char*)"120048833")
#define MOD_AUTHOR_CPF                          ((char*)"024.723.347-10")
#define MOD_AUTHOR_ID                           ((char*)"08855128-8 IFP-RJ")
#define MOD_AUTHOR_PHONE                        ((char*)"+55-21-99983-7207")
#define MOD_AUTHOR_EMAIL1                       ((char*)"lmarcio@cos.ufrj.br")
#define MOD_AUTHOR_EMAIL2                       ((char*)"luiz.marcio.viana@globo.com")
#define MOD_AUTHOR_EMAIL3                       ((char*)"luiz.marcio.viana@gmail.com")

#define RSERR                                   -1
#define RSOK                                    0

#define FALSE                                   0
#define TRUE                                    1 

#define DEF_MAX_VALUE                           9999999.0
#define DEF_MIN_VALUE                           -9999999.0

#define DEF_INPUT_FILENAME                      ((char*)"_DATASETS/a5.tsp")
//#define DEF_INPUT_FILENAME                      ((char*)"_DATASETS/a6.tsp")
//#define DEF_INPUT_FILENAME                      ((char*)"_DATASETS/a7.tsp")
//#define DEF_INPUT_FILENAME                      ((char*)"_DATASETS/a8.tsp")
//#define DEF_INPUT_FILENAME                      ((char*)"_DATASETS/a9.tsp")
//#define DEF_INPUT_FILENAME                      ((char*)"_DATASETS/a10.tsp")
//#define DEF_INPUT_FILENAME                      ((char*)"_DATASETS/a11.tsp")
//#define DEF_INPUT_FILENAME                      ((char*)"_DATASETS/a12.tsp")

#define DEF_SHOWDATA_MAX_ITEMS                  1024

#define DEF_SHOWDATA_MAX_ROWS                   25

#define DEF_NUM_OF_THREADS                      2

#define DEF_NUM_OF_TSPTAGS                      7

#define DEF_RESULT_NUM_TESTS                    9       /* FORCABRUTA + HEURISTICA */

#define DEF_TSP_FORCABRUTA                      0
#define DEF_TSP_FORCABRUTA_OPENMP               1
#define DEF_TSP_FORCABRUTA_OPENMPI              2
#define DEF_TSP_ALGO_COMPLETO                   3
#define DEF_TSP_ALGO_COMPLETO_OPENMP            4
#define DEF_TSP_ALGO_COMPLETO_OPENMPI           5
#define DEF_TSP_HEURISTICA                      6
#define DEF_TSP_HEURISTICA_OPENMP               7
#define DEF_TSP_HEURISTICA_OPENMPI              8

#define DEF_CASESENSITIVE_NONE                  0
#define DEF_CASESENSITIVE_TOUPPER               1
#define DEF_CASESENSITIVE_TOLOWER               4

#define FILMODE_READ                            ((char*)"r")
#define FILMODE_READ_WRITE                      ((char*)"r+")
#define FILMODE_WRITE                           ((char*)"w")
#define FILMODE_WRITE_TRUNCATE_DATA             ((char*)"w+")
#define FILMODE_APPEND                          ((char*)"a")
#define FILMODE_READ_APPEND                     ((char*)"a+")

#define MIN(X,Y)                                ((X < Y) ? X : Y)
#define MAX(X,Y)                                ((X > Y) ? X : Y)

#define IFNULL(X,Y)                             ((X == NULL) ? Y : X)

/* Data Types */

typedef unsigned char byte;

/* String Definition */

#define STRSZ                                   32

typedef char str_t[STRSZ];

#define BIGSTRSZ                                256

typedef char bigstr_t[BIGSTRSZ];

/* TSP Calculate Distance */

#define TSP_CALC_EUCL_DIST                      1001
#define TSP_CALC_MANH_DIST                      1002
#define TSP_CALC_MAX_DIST                       1003
#define TSP_CALC_GEO_DIST                       1004
#define TSP_CALC_PSEUDO_EUCL_DIST               1005
#define TSP_CALC_CEIL_EUCL_DIST                 1006

/* TSP File Tags */

#define TSP_TAG_NAME                            ((char*)"NAME")
#define TSP_TAG_COMMENT                         ((char*)"COMMENT")
#define TSP_TAG_TYPE                            ((char*)"TYPE")
#define TSP_TAG_DIMENSION                       ((char*)"DIMENSION")
#define TSP_TAG_EDGE_WEIGHT_TYPE                ((char*)"EDGE_WEIGHT_TYPE")
#define TSP_TAG_NODE_COORD_SECTION              ((char*)"NODE_COORD_SECTION")
#define TSP_TAG_NODE_ENTRY                      ((char*)"NODE_ENTRY")
#define TSP_TAG_EOF                             ((char*)"EOF")

/* TSP ID Tags */

#define TSP_TAGID_NONE                          -1
#define TSP_TAGID_NAME                          5001
#define TSP_TAGID_COMMENT                       5002
#define TSP_TAGID_TYPE                          5003
#define TSP_TAGID_DIMENSION                     5004
#define TSP_TAGID_EDGE_WEIGHT_TYPE              5005
#define TSP_TAGID_NODE_COORD_SECTION            5006
#define TSP_TAGID_NODE_ENTRY                    5007
#define TSP_TAGID_EOF                           5008

/* Value Result */

#define RESVAL_THREADID                         0
#define RESVAL_STARTDATA                        1
#define RESVAL_DATASIZE                         2

#define NUM_RESVAL_ENTRIES                      3

typedef char* charptr_t;

typedef long* longptr_t;

typedef struct resbuf_struct {
    long resval[NUM_RESVAL_ENTRIES];
} resbuf_t;

/* Data Test */

typedef struct datavaltest_struct {
    long datavaltest_dimension;
    long datavaltest_start_time;
    long datavaltest_end_time;
    long datavaltest_elapsed_time;
    double datavaltest_initial_cost;
    double datavaltest_final_cost;
} datavaltest_t;

typedef struct datatest_struct {
    bigstr_t datatest_title;
    bigstr_t datatest_name;
    bigstr_t datatest_comment;
    bigstr_t datatest_type;
    bigstr_t datatest_edge_weight_type;
    datavaltest_t datatest_val;
} datatest_t;

/* Data Token */

typedef struct datatoken_struct {
    long datatoken_type;
    long datatoken_oid;
    long datatoken_selected;
    long datatoken_processed;
    long datatoken_order;
    double datatoken_xp;
    double datatoken_yp;
    double datatoken_dist;
} datatoken_t;

typedef struct datatokenptr_struct {
    datatoken_t* initial_dataptr;
    datatoken_t* dataptr;
    long datatoken_initial_order;
    long datatoken_order;
    long datatoken_step;
    double datatoken_dist;
} datatokenptr_t;

#endif
