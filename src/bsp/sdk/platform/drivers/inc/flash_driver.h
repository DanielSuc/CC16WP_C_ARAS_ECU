
#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

#include <stdbool.h>
#include <stddef.h>
#include "status.h"
#include "device_registers.h"


#ifdef FTFE
#define FTFx_BASE                               FTFE_BASE
#define FTFx_FSTAT                              FTFE->FSTAT
#define FTFx_FCNFG                              FTFE->FCNFG
#define FTFx_FSEC                               FTFE->FSEC
#define FTFx_FOPT                               FTFE->FOPT
#define FTFx_FCCOB3                             FTFE->FCCOB[0]
#define FTFx_FCCOB2                             FTFE->FCCOB[1]
#define FTFx_FCCOB1                             FTFE->FCCOB[2]
#define FTFx_FCCOB0                             FTFE->FCCOB[3]
#define FTFx_FCCOB7                             FTFE->FCCOB[4]
#define FTFx_FCCOB6                             FTFE->FCCOB[5]
#define FTFx_FCCOB5                             FTFE->FCCOB[6]
#define FTFx_FCCOB4                             FTFE->FCCOB[7]
#define FTFx_FCCOBB                             FTFE->FCCOB[8]
#define FTFx_FCCOBA                             FTFE->FCCOB[9]
#define FTFx_FCCOB9                             FTFE->FCCOB[10]
#define FTFx_FCCOB8                             FTFE->FCCOB[11]
#define FTFx_FPROT3                             FTFE->FPROT[0]
#define FTFx_FPROT2                             FTFE->FPROT[1]
#define FTFx_FPROT1                             FTFE->FPROT[2]
#define FTFx_FPROT0                             FTFE->FPROT[3]
#define FTFx_FEPROT                             FTFE->FEPROT
#define FTFx_FDPROT                             FTFE->FDPROT
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
#define FTFx_FERSTAT                            FTFE->FERSTAT
#define FTFx_FERCNFG                            FTFE->FERCNFG
#endif
#define FTFx_FSTAT_MGSTAT0_MASK                 FTFE_FSTAT_MGSTAT0_MASK
#define FTFx_FSTAT_MGSTAT0_SHIFT                FTFE_FSTAT_MGSTAT0_SHIFT
#define FTFx_FSTAT_MGSTAT0_WIDTH                FTFE_FSTAT_MGSTAT0_WIDTH
#define FTFx_FSTAT_MGSTAT0(x)                   FTFE_FSTAT_MGSTAT0(x)
#define FTFx_FSTAT_FPVIOL_MASK                  FTFE_FSTAT_FPVIOL_MASK
#define FTFx_FSTAT_FPVIOL_SHIFT                 FTFE_FSTAT_FPVIOL_SHIFT
#define FTFx_FSTAT_FPVIOL_WIDTH                 FTFE_FSTAT_FPVIOL_WIDTH
#define FTFx_FSTAT_FPVIOL(x)                    FTFE_FSTAT_FPVIOL(x)
#define FTFx_FSTAT_ACCERR_MASK                  FTFE_FSTAT_ACCERR_MASK
#define FTFx_FSTAT_ACCERR_SHIFT                 FTFE_FSTAT_ACCERR_SHIFT
#define FTFx_FSTAT_ACCERR_WIDTH                 FTFE_FSTAT_ACCERR_WIDTH
#define FTFx_FSTAT_ACCERR(x)                    FTFE_FSTAT_ACCERR(x)
#define FTFx_FSTAT_RDCOLERR_MASK                FTFE_FSTAT_RDCOLERR_MASK
#define FTFx_FSTAT_RDCOLERR_SHIFT               FTFE_FSTAT_RDCOLERR_SHIFT
#define FTFx_FSTAT_RDCOLERR_WIDTH               FTFE_FSTAT_RDCOLERR_WIDTH
#define FTFx_FSTAT_RDCOLERR(x)                  FTFE_FSTAT_RDCOLERR(x)
#define FTFx_FSTAT_CCIF_MASK                    FTFE_FSTAT_CCIF_MASK
#define FTFx_FSTAT_CCIF_SHIFT                   FTFE_FSTAT_CCIF_SHIFT
#define FTFx_FSTAT_CCIF_WIDTH                   FTFE_FSTAT_CCIF_WIDTH
#define FTFx_FSTAT_CCIF(x)                      FTFE_FSTAT_CCIF(x)
#define FTFx_FCNFG_EEERDY_MASK                  FTFE_FCNFG_EEERDY_MASK
#define FTFx_FCNFG_EEERDY_SHIFT                 FTFE_FCNFG_EEERDY_SHIFT
#define FTFx_FCNFG_EEERDY_WIDTH                 FTFE_FCNFG_EEERDY_WIDTH
#define FTFx_FCNFG_EEERDY(x)                    FTFE_FCNFG_EEERDY(x)
#define FTFx_FCNFG_RAMRDY_MASK                  FTFE_FCNFG_RAMRDY_MASK
#define FTFx_FCNFG_RAMRDY_SHIFT                 FTFE_FCNFG_RAMRDY_SHIFT
#define FTFx_FCNFG_RAMRDY_WIDTH                 FTFE_FCNFG_RAMRDY_WIDTH
#define FTFx_FCNFG_RAMRDY(x)                    FTFE_FCNFG_RAMRDY(x)
#define FTFx_FCNFG_PFLSH_MASK                   FTFE_FCNFG_PFLSH_MASK
#define FTFx_FCNFG_PFLSH_SHIFT                  FTFE_FCNFG_PFLSH_SHIFT
#define FTFx_FCNFG_PFLSH_WIDTH                  FTFE_FCNFG_PFLSH_WIDTH
#define FTFx_FCNFG_PFLSH(x)                     FTFE_FCNFG_PFLSH(x)
#define FTFx_FCNFG_ERSSUSP_MASK                 FTFE_FCNFG_ERSSUSP_MASK
#define FTFx_FCNFG_ERSSUSP_SHIFT                FTFE_FCNFG_ERSSUSP_SHIFT
#define FTFx_FCNFG_ERSSUSP_WIDTH                FTFE_FCNFG_ERSSUSP_WIDTH
#define FTFx_FCNFG_ERSSUSP(x)                   FTFE_FCNFG_ERSSUSP(x)
#define FTFx_FCNFG_ERSAREQ_MASK                 FTFE_FCNFG_ERSAREQ_MASK
#define FTFx_FCNFG_ERSAREQ_SHIFT                FTFE_FCNFG_ERSAREQ_SHIFT
#define FTFx_FCNFG_ERSAREQ_WIDTH                FTFE_FCNFG_ERSAREQ_WIDTH
#define FTFx_FCNFG_ERSAREQ(x)                   FTFE_FCNFG_ERSAREQ(x)
#define FTFx_FCNFG_RDCOLLIE_MASK                FTFE_FCNFG_RDCOLLIE_MASK
#define FTFx_FCNFG_RDCOLLIE_SHIFT               FTFE_FCNFG_RDCOLLIE_SHIFT
#define FTFx_FCNFG_RDCOLLIE_WIDTH               FTFE_FCNFG_RDCOLLIE_WIDTH
#define FTFx_FCNFG_RDCOLLIE(x)                  FTFE_FCNFG_RDCOLLIE(x)
#define FTFx_FCNFG_CCIE_MASK                    FTFE_FCNFG_CCIE_MASK
#define FTFx_FCNFG_CCIE_SHIFT                   FTFE_FCNFG_CCIE_SHIFT
#define FTFx_FCNFG_CCIE_WIDTH                   FTFE_FCNFG_CCIE_WIDTH
#define FTFx_FCNFG_CCIE(x)                      FTFE_FCNFG_CCIE(x)
#define FTFx_FSEC_SEC_MASK                      FTFE_FSEC_SEC_MASK
#define FTFx_FSEC_SEC_SHIFT                     FTFE_FSEC_SEC_SHIFT
#define FTFx_FSEC_SEC_WIDTH                     FTFE_FSEC_SEC_WIDTH
#define FTFx_FSEC_SEC(x)                        FTFE_FSEC_SEC(x)
#define FTFx_FSEC_FSLACC_MASK                   FTFE_FSEC_FSLACC_MASK
#define FTFx_FSEC_FSLACC_SHIFT                  FTFE_FSEC_FSLACC_SHIFT
#define FTFx_FSEC_FSLACC_WIDTH                  FTFE_FSEC_FSLACC_WIDTH
#define FTFx_FSEC_FSLACC(x)                     FTFE_FSEC_FSLACC(x)
#define FTFx_FSEC_MEEN_MASK                     FTFE_FSEC_MEEN_MASK
#define FTFx_FSEC_MEEN_SHIFT                    FTFE_FSEC_MEEN_SHIFT
#define FTFx_FSEC_MEEN_WIDTH                    FTFE_FSEC_MEEN_WIDTH
#define FTFx_FSEC_MEEN(x)                       FTFE_FSEC_MEEN(x)
#define FTFx_FSEC_KEYEN_MASK                    FTFE_FSEC_KEYEN_MASK
#define FTFx_FSEC_KEYEN_SHIFT                   FTFE_FSEC_KEYEN_SHIFT
#define FTFx_FSEC_KEYEN_WIDTH                   FTFE_FSEC_KEYEN_WIDTH
#define FTFx_FSEC_KEYEN(x)                      FTFE_FSEC_KEYEN(x)
#define FTFx_FOPT_OPT_MASK                      FTFE_FOPT_OPT_MASK
#define FTFx_FOPT_OPT_SHIFT                     FTFE_FOPT_OPT_SHIFT
#define FTFx_FOPT_OPT_WIDTH                     FTFE_FOPT_OPT_WIDTH
#define FTFx_FOPT_OPT(x)                        FTFE_FOPT_OPT(x)
#define FTFx_FCCOB_CCOBn_MASK                   FTFE_FCCOB_CCOBn_MASK
#define FTFx_FCCOB_CCOBn_SHIFT                  FTFE_FCCOB_CCOBn_SHIFT
#define FTFx_FCCOB_CCOBn_WIDTH                  FTFE_FCCOB_CCOBn_WIDTH
#define FTFx_FCCOB_CCOBn(x)                     FTFE_FCCOB_CCOBn(x)
#define FTFx_FPROT_PROT_MASK                    FTFE_FPROT_PROT_MASK
#define FTFx_FPROT_PROT_SHIFT                   FTFE_FPROT_PROT_SHIFT
#define FTFx_FPROT_PROT_WIDTH                   FTFE_FPROT_PROT_WIDTH
#define FTFx_FPROT_PROT(x)                      FTFE_FPROT_PROT(x)
#define FTFx_FEPROT_EPROT_MASK                  FTFE_FEPROT_EPROT_MASK
#define FTFx_FEPROT_EPROT_SHIFT                 FTFE_FEPROT_EPROT_SHIFT
#define FTFx_FEPROT_EPROT_WIDTH                 FTFE_FEPROT_EPROT_WIDTH
#define FTFx_FEPROT_EPROT(x)                    FTFE_FEPROT_EPROT(x)
#define FTFx_FDPROT_DPROT_MASK                  FTFE_FDPROT_DPROT_MASK
#define FTFx_FDPROT_DPROT_SHIFT                 FTFE_FDPROT_DPROT_SHIFT
#define FTFx_FDPROT_DPROT_WIDTH                 FTFE_FDPROT_DPROT_WIDTH
#define FTFx_FDPROT_DPROT(x)                    FTFE_FDPROT_DPROT(x)
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
#define FTFx_FERSTAT_DFDIF_MASK                 FTFE_FERSTAT_DFDIF_MASK
#define FTFx_FERSTAT_DFDIF_SHIFT                FTFE_FERSTAT_DFDIF_SHIFT
#define FTFx_FERSTAT_DFDIF_WIDTH                FTFE_FERSTAT_DFDIF_WIDTH
#define FTFx_FERSTAT_DFDIF(x)                   FTFE_FERSTAT_DFDIF(x)
#define FTFx_FERCNFG_DFDIE_MASK                 FTFE_FERCNFG_DFDIE_MASK
#define FTFx_FERCNFG_DFDIE_SHIFT                FTFE_FERCNFG_DFDIE_SHIFT
#define FTFx_FERCNFG_DFDIE_WIDTH                FTFE_FERCNFG_DFDIE_WIDTH
#define FTFx_FERCNFG_DFDIE(x)                   FTFE_FERCNFG_DFDIE(x)
#define FTFx_FERCNFG_FDFD_MASK                  FTFE_FERCNFG_FDFD_MASK
#define FTFx_FERCNFG_FDFD_SHIFT                 FTFE_FERCNFG_FDFD_SHIFT
#define FTFx_FERCNFG_FDFD_WIDTH                 FTFE_FERCNFG_FDFD_WIDTH
#define FTFx_FERCNFG_FDFD(x)                    FTFE_FERCNFG_FDFD(x)
#endif
#elif defined(FTFC)
#define FTFx_BASE                               FTFC_BASE
#define FTFx_FSTAT                              FTFC->FSTAT
#define FTFx_FCNFG                              FTFC->FCNFG
#define FTFx_FSEC                               FTFC->FSEC
#define FTFx_FOPT                               FTFC->FOPT
#define FTFx_FCCOB3                             FTFC->FCCOB[0]
#define FTFx_FCCOB2                             FTFC->FCCOB[1]
#define FTFx_FCCOB1                             FTFC->FCCOB[2]
#define FTFx_FCCOB0                             FTFC->FCCOB[3]
#define FTFx_FCCOB7                             FTFC->FCCOB[4]
#define FTFx_FCCOB6                             FTFC->FCCOB[5]
#define FTFx_FCCOB5                             FTFC->FCCOB[6]
#define FTFx_FCCOB4                             FTFC->FCCOB[7]
#define FTFx_FCCOBB                             FTFC->FCCOB[8]
#define FTFx_FCCOBA                             FTFC->FCCOB[9]
#define FTFx_FCCOB9                             FTFC->FCCOB[10]
#define FTFx_FCCOB8                             FTFC->FCCOB[11]
#define FTFx_FPROT3                             FTFC->FPROT[0]
#define FTFx_FPROT2                             FTFC->FPROT[1]
#define FTFx_FPROT1                             FTFC->FPROT[2]
#define FTFx_FPROT0                             FTFC->FPROT[3]
#define FTFx_FEPROT                             FTFC->FEPROT
#define FTFx_FDPROT                             FTFC->FDPROT
#define FTFx_FCSESTAT                           FTFC->FCSESTAT
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
#define FTFx_FERSTAT                            FTFC->FERSTAT
#define FTFx_FERCNFG                            FTFC->FERCNFG
#endif
#define FTFx_FSTAT_MGSTAT0_MASK                 FTFC_FSTAT_MGSTAT0_MASK
#define FTFx_FSTAT_MGSTAT0_SHIFT                FTFC_FSTAT_MGSTAT0_SHIFT
#define FTFx_FSTAT_MGSTAT0_WIDTH                FTFC_FSTAT_MGSTAT0_WIDTH
#define FTFx_FSTAT_MGSTAT0(x)                   FTFC_FSTAT_MGSTAT0(x)
#define FTFx_FSTAT_FPVIOL_MASK                  FTFC_FSTAT_FPVIOL_MASK
#define FTFx_FSTAT_FPVIOL_SHIFT                 FTFC_FSTAT_FPVIOL_SHIFT
#define FTFx_FSTAT_FPVIOL_WIDTH                 FTFC_FSTAT_FPVIOL_WIDTH
#define FTFx_FSTAT_FPVIOL(x)                    FTFC_FSTAT_FPVIOL(x)
#define FTFx_FSTAT_ACCERR_MASK                  FTFC_FSTAT_ACCERR_MASK
#define FTFx_FSTAT_ACCERR_SHIFT                 FTFC_FSTAT_ACCERR_SHIFT
#define FTFx_FSTAT_ACCERR_WIDTH                 FTFC_FSTAT_ACCERR_WIDTH
#define FTFx_FSTAT_ACCERR(x)                    FTFC_FSTAT_ACCERR(x)
#define FTFx_FSTAT_RDCOLERR_MASK                FTFC_FSTAT_RDCOLERR_MASK
#define FTFx_FSTAT_RDCOLERR_SHIFT               FTFC_FSTAT_RDCOLERR_SHIFT
#define FTFx_FSTAT_RDCOLERR_WIDTH               FTFC_FSTAT_RDCOLERR_WIDTH
#define FTFx_FSTAT_RDCOLERR(x)                  FTFC_FSTAT_RDCOLERR(x)
#define FTFx_FSTAT_CCIF_MASK                    FTFC_FSTAT_CCIF_MASK
#define FTFx_FSTAT_CCIF_SHIFT                   FTFC_FSTAT_CCIF_SHIFT
#define FTFx_FSTAT_CCIF_WIDTH                   FTFC_FSTAT_CCIF_WIDTH
#define FTFx_FSTAT_CCIF(x)                      FTFC_FSTAT_CCIF(x)
#define FTFx_FCNFG_EEERDY_MASK                  FTFC_FCNFG_EEERDY_MASK
#define FTFx_FCNFG_EEERDY_SHIFT                 FTFC_FCNFG_EEERDY_SHIFT
#define FTFx_FCNFG_EEERDY_WIDTH                 FTFC_FCNFG_EEERDY_WIDTH
#define FTFx_FCNFG_EEERDY(x)                    FTFC_FCNFG_EEERDY(x)
#define FTFx_FCNFG_RAMRDY_MASK                  FTFC_FCNFG_RAMRDY_MASK
#define FTFx_FCNFG_RAMRDY_SHIFT                 FTFC_FCNFG_RAMRDY_SHIFT
#define FTFx_FCNFG_RAMRDY_WIDTH                 FTFC_FCNFG_RAMRDY_WIDTH
#define FTFx_FCNFG_RAMRDY(x)                    FTFC_FCNFG_RAMRDY(x)
#define FTFx_FCNFG_ERSSUSP_MASK                 FTFC_FCNFG_ERSSUSP_MASK
#define FTFx_FCNFG_ERSSUSP_SHIFT                FTFC_FCNFG_ERSSUSP_SHIFT
#define FTFx_FCNFG_ERSSUSP_WIDTH                FTFC_FCNFG_ERSSUSP_WIDTH
#define FTFx_FCNFG_ERSSUSP(x)                   FTFC_FCNFG_ERSSUSP(x)
#define FTFx_FCNFG_ERSAREQ_MASK                 FTFC_FCNFG_ERSAREQ_MASK
#define FTFx_FCNFG_ERSAREQ_SHIFT                FTFC_FCNFG_ERSAREQ_SHIFT
#define FTFx_FCNFG_ERSAREQ_WIDTH                FTFC_FCNFG_ERSAREQ_WIDTH
#define FTFx_FCNFG_ERSAREQ(x)                   FTFC_FCNFG_ERSAREQ(x)
#define FTFx_FCNFG_RDCOLLIE_MASK                FTFC_FCNFG_RDCOLLIE_MASK
#define FTFx_FCNFG_RDCOLLIE_SHIFT               FTFC_FCNFG_RDCOLLIE_SHIFT
#define FTFx_FCNFG_RDCOLLIE_WIDTH               FTFC_FCNFG_RDCOLLIE_WIDTH
#define FTFx_FCNFG_RDCOLLIE(x)                  FTFC_FCNFG_RDCOLLIE(x)
#define FTFx_FCNFG_CCIE_MASK                    FTFC_FCNFG_CCIE_MASK
#define FTFx_FCNFG_CCIE_SHIFT                   FTFC_FCNFG_CCIE_SHIFT
#define FTFx_FCNFG_CCIE_WIDTH                   FTFC_FCNFG_CCIE_WIDTH
#define FTFx_FCNFG_CCIE(x)                      FTFC_FCNFG_CCIE(x)
#define FTFx_FSEC_SEC_MASK                      FTFC_FSEC_SEC_MASK
#define FTFx_FSEC_SEC_SHIFT                     FTFC_FSEC_SEC_SHIFT
#define FTFx_FSEC_SEC_WIDTH                     FTFC_FSEC_SEC_WIDTH
#define FTFx_FSEC_SEC(x)                        FTFC_FSEC_SEC(x)
#define FTFx_FSEC_FSLACC_MASK                   FTFC_FSEC_FSLACC_MASK
#define FTFx_FSEC_FSLACC_SHIFT                  FTFC_FSEC_FSLACC_SHIFT
#define FTFx_FSEC_FSLACC_WIDTH                  FTFC_FSEC_FSLACC_WIDTH
#define FTFx_FSEC_FSLACC(x)                     FTFC_FSEC_FSLACC(x)
#define FTFx_FSEC_MEEN_MASK                     FTFC_FSEC_MEEN_MASK
#define FTFx_FSEC_MEEN_SHIFT                    FTFC_FSEC_MEEN_SHIFT
#define FTFx_FSEC_MEEN_WIDTH                    FTFC_FSEC_MEEN_WIDTH
#define FTFx_FSEC_MEEN(x)                       FTFC_FSEC_MEEN(x)
#define FTFx_FSEC_KEYEN_MASK                    FTFC_FSEC_KEYEN_MASK
#define FTFx_FSEC_KEYEN_SHIFT                   FTFC_FSEC_KEYEN_SHIFT
#define FTFx_FSEC_KEYEN_WIDTH                   FTFC_FSEC_KEYEN_WIDTH
#define FTFx_FSEC_KEYEN(x)                      FTFC_FSEC_KEYEN(x)
#define FTFx_FOPT_OPT_MASK                      FTFC_FOPT_OPT_MASK
#define FTFx_FOPT_OPT_SHIFT                     FTFC_FOPT_OPT_SHIFT
#define FTFx_FOPT_OPT_WIDTH                     FTFC_FOPT_OPT_WIDTH
#define FTFx_FOPT_OPT(x)                        FTFC_FOPT_OPT(x)
#define FTFx_FCCOB_CCOBn_MASK                   FTFC_FCCOB_CCOBn_MASK
#define FTFx_FCCOB_CCOBn_SHIFT                  FTFC_FCCOB_CCOBn_SHIFT
#define FTFx_FCCOB_CCOBn_WIDTH                  FTFC_FCCOB_CCOBn_WIDTH
#define FTFx_FCCOB_CCOBn(x)                     FTFC_FCCOB_CCOBn(x)
#define FTFx_FPROT_PROT_MASK                    FTFC_FPROT_PROT_MASK
#define FTFx_FPROT_PROT_SHIFT                   FTFC_FPROT_PROT_SHIFT
#define FTFx_FPROT_PROT_WIDTH                   FTFC_FPROT_PROT_WIDTH
#define FTFx_FPROT_PROT(x)                      FTFC_FPROT_PROT(x)
#define FTFx_FEPROT_EPROT_MASK                  FTFC_FEPROT_EPROT_MASK
#define FTFx_FEPROT_EPROT_SHIFT                 FTFC_FEPROT_EPROT_SHIFT
#define FTFx_FEPROT_EPROT_WIDTH                 FTFC_FEPROT_EPROT_WIDTH
#define FTFx_FEPROT_EPROT(x)                    FTFC_FEPROT_EPROT(x)
#define FTFx_FDPROT_DPROT_MASK                  FTFC_FDPROT_DPROT_MASK
#define FTFx_FDPROT_DPROT_SHIFT                 FTFC_FDPROT_DPROT_SHIFT
#define FTFx_FDPROT_DPROT_WIDTH                 FTFC_FDPROT_DPROT_WIDTH
#define FTFx_FDPROT_DPROT(x)                    FTFC_FDPROT_DPROT(x)
#define FTFx_FCSESTAT_IDB_MASK                  FTFC_FCSESTAT_IDB_MASK
#define FTFx_FCSESTAT_IDB_SHIFT                 FTFC_FCSESTAT_IDB_SHIFT
#define FTFx_FCSESTAT_IDB_WIDTH                 FTFC_FCSESTAT_IDB_WIDTH
#define FTFx_FCSESTAT_IDB(x)                    FTFC_FCSESTAT_IDB(x)
#define FTFx_FCSESTAT_EDB_MASK                  FTFC_FCSESTAT_EDB_MASK
#define FTFx_FCSESTAT_EDB_SHIFT                 FTFC_FCSESTAT_EDB_SHIFT
#define FTFx_FCSESTAT_EDB_WIDTH                 FTFC_FCSESTAT_EDB_WIDTH
#define FTFx_FCSESTAT_EDB(x)                    FTFC_FCSESTAT_EDB(x)
#define FTFx_FCSESTAT_RIN_MASK                  FTFC_FCSESTAT_RIN_MASK
#define FTFx_FCSESTAT_RIN_SHIFT                 FTFC_FCSESTAT_RIN_SHIFT
#define FTFx_FCSESTAT_RIN_WIDTH                 FTFC_FCSESTAT_RIN_WIDTH
#define FTFx_FCSESTAT_RIN(x)                    FTFC_FCSESTAT_RIN(x)
#define FTFx_FCSESTAT_BOK_MASK                  FTFC_FCSESTAT_BOK_MASK
#define FTFx_FCSESTAT_BOK_SHIFT                 FTFC_FCSESTAT_BOK_SHIFT
#define FTFx_FCSESTAT_BOK_WIDTH                 FTFC_FCSESTAT_BOK_WIDTH
#define FTFx_FCSESTAT_BOK(x)                    FTFC_FCSESTAT_BOK(x)
#define FTFx_FCSESTAT_BFN_MASK                  FTFC_FCSESTAT_BFN_MASK
#define FTFx_FCSESTAT_BFN_SHIFT                 FTFC_FCSESTAT_BFN_SHIFT
#define FTFx_FCSESTAT_BFN_WIDTH                 FTFC_FCSESTAT_BFN_WIDTH
#define FTFx_FCSESTAT_BFN(x)                    FTFC_FCSESTAT_BFN(x)
#define FTFx_FCSESTAT_BIN_MASK                  FTFC_FCSESTAT_BIN_MASK
#define FTFx_FCSESTAT_BIN_SHIFT                 FTFC_FCSESTAT_BIN_SHIFT
#define FTFx_FCSESTAT_BIN_WIDTH                 FTFC_FCSESTAT_BIN_WIDTH
#define FTFx_FCSESTAT_BIN(x)                    FTFC_FCSESTAT_BIN(x)
#define FTFx_FCSESTAT_SB_MASK                   FTFC_FCSESTAT_SB_MASK
#define FTFx_FCSESTAT_SB_SHIFT                  FTFC_FCSESTAT_SB_SHIFT
#define FTFx_FCSESTAT_SB_WIDTH                  FTFC_FCSESTAT_SB_WIDTH
#define FTFx_FCSESTAT_SB(x)                     FTFC_FCSESTAT_SB(x)
#define FTFx_FCSESTAT_BSY_MASK                  FTFC_FCSESTAT_BSY_MASK
#define FTFx_FCSESTAT_BSY_SHIFT                 FTFC_FCSESTAT_BSY_SHIFT
#define FTFx_FCSESTAT_BSY_WIDTH                 FTFC_FCSESTAT_BSY_WIDTH
#define FTFx_FCSESTAT_BSY(x)                    FTFC_FCSESTAT_BSY(x)
#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
#define FTFx_FERSTAT_DFDIF_MASK                 FTFC_FERSTAT_DFDIF_MASK
#define FTFx_FERSTAT_DFDIF_SHIFT                FTFC_FERSTAT_DFDIF_SHIFT
#define FTFxFERSTAT_DFDIF_WIDTH                 FTFC_FERSTAT_DFDIF_WIDTH
#define FTFx_FERSTAT_DFDIF(x)                   FTFC_FERSTAT_DFDIF(x)
#define FTFx_FERCNFG_DFDIE_MASK                 FTFC_FERCNFG_DFDIE_MASK
#define FTFx_FERCNFG_DFDIE_SHIFT                FTFC_FERCNFG_DFDIE_SHIFT
#define FTFx_FERCNFG_DFDIE_WIDTH                FTFC_FERCNFG_DFDIE_WIDTH
#define FTFx_FERCNFG_DFDIE(x)                   FTFC_FERCNFG_DFDIE(x)
#define FTFx_FERCNFG_FDFD_MASK                  FTFC_FERCNFG_FDFD_MASK
#define FTFx_FERCNFG_FDFD_SHIFT                 FTFC_FERCNFG_FDFD_SHIFT
#define FTFx_FERCNFG_FDFD_WIDTH                 FTFC_FERCNFG_FDFD_WIDTH
#define FTFx_FERCNFG_FDFD(x)                    FTFC_FERCNFG_FDFD(x)
#endif

#else  
#endif 


#define CLEAR_FTFx_FSTAT_ERROR_BITS FTFx_FSTAT = (uint8_t)(FTFx_FSTAT_FPVIOL_MASK | FTFx_FSTAT_ACCERR_MASK | FTFx_FSTAT_RDCOLERR_MASK)

#define FTFx_WORD_SIZE     0x0002U
#define FTFx_LONGWORD_SIZE 0x0004U
#define FTFx_PHRASE_SIZE   0x0008U
#define FTFx_DPHRASE_SIZE  0x0010U

#if (FEATURE_FLS_PF_BLOCK_WRITE_UNIT_SIZE == FTFx_PHRASE_SIZE)
#define FTFx_RSRC_CODE_REG FTFx_FCCOB4
#else
#define FTFx_RSRC_CODE_REG FTFx_FCCOB8
#endif

#define FTFx_VERIFY_BLOCK             0x00U
#define FTFx_VERIFY_SECTION           0x01U
#define FTFx_PROGRAM_CHECK            0x02U
#define FTFx_READ_RESOURCE            0x03U
#define FTFx_PROGRAM_LONGWORD         0x06U
#define FTFx_PROGRAM_PHRASE           0x07U
#define FTFx_ERASE_BLOCK              0x08U
#define FTFx_ERASE_SECTOR             0x09U
#define FTFx_PROGRAM_SECTION          0x0BU
#define FTFx_VERIFY_ALL_BLOCK         0x40U
#define FTFx_READ_ONCE                0x41U
#define FTFx_PROGRAM_ONCE             0x43U
#define FTFx_ERASE_ALL_BLOCK          0x44U
#define FTFx_SECURITY_BY_PASS         0x45U
#define FTFx_PFLASH_SWAP              0x46U
#define FTFx_ERASE_ALL_BLOCK_UNSECURE 0x49U
#define FTFx_PROGRAM_PARTITION        0x80U
#define FTFx_SET_EERAM                0x81U


#define FTFx_SWAP_SET_INDICATOR_ADDR 0x01U
#define FTFx_SWAP_SET_IN_PREPARE     0x02U
#define FTFx_SWAP_SET_IN_COMPLETE    0x04U
#define FTFx_SWAP_REPORT_STATUS      0x08U

#define FTFx_SWAP_UNINIT        0x00U
#define FTFx_SWAP_READY         0x01U
#define FTFx_SWAP_UPDATE        0x02U
#define FTFx_SWAP_UPDATE_ERASED 0x03U
#define FTFx_SWAP_COMPLETE      0x04U

#define RESUME_WAIT_CNT         0x20U
#define SUSPEND_WAIT_CNT        0x40U

#if (FEATURE_FLS_IS_FTFE == 1U)
#define DFLASH_IFR_READRESOURCE_ADDRESS 0x8003F8U
#else 
#define DFLASH_IFR_READRESOURCE_ADDRESS 0x8000FCU
#endif

#define GET_BIT_0_7(value)   ((uint8_t)(((uint32_t)(value)) & 0xFFU))
#define GET_BIT_8_15(value)  ((uint8_t)((((uint32_t)(value)) >> 8) & 0xFFU))
#define GET_BIT_16_23(value) ((uint8_t)((((uint32_t)(value)) >> 16) & 0xFFU))
#define GET_BIT_24_31(value) ((uint8_t)(((uint32_t)(value)) >> 24))

#define FLASH_SECURITY_STATE_KEYEN     0x80U
#define FLASH_SECURITY_STATE_UNSECURED 0x02U

#define CSE_KEY_SIZE_CODE_MAX 0x03U


typedef enum
{
    EEE_ENABLE                              = 0x00U,    
    EEE_QUICK_WRITE                         = 0x55U,    
    EEE_STATUS_QUERY                        = 0x77U,    
    EEE_COMPLETE_INTERRUPT_QUICK_WRITE      = 0xAAU,    
    EEE_DISABLE                             = 0xFFU,    
} flash_flexRam_function_control_code_t;

#define FLASH_NOT_SECURE               0x01U
#define FLASH_SECURE_BACKDOOR_ENABLED  0x02U
#define FLASH_SECURE_BACKDOOR_DISABLED 0x04U

#ifndef FLASH_CALLBACK_CS
#define FLASH_CALLBACK_CS 0x0AU
#endif

#define NULL_CALLBACK      ((flash_callback_t)0xFFFFFFFFU)

#if FEATURE_FLS_HAS_PF_BLOCK_SWAP
#define NULL_SWAP_CALLBACK ((flash_swap_callback_t)0xFFFFFFFFU)
#endif

typedef void (* flash_callback_t)(void);
#if FEATURE_FLS_HAS_PF_BLOCK_SWAP
typedef bool (* flash_swap_callback_t)(uint8_t function);
#endif

typedef struct
{
    uint32_t PFlashBase;            
    uint32_t PFlashSize;            
    uint32_t DFlashBase;            
    uint32_t EERAMBase;             
    flash_callback_t CallBack;      
} flash_user_config_t;

typedef struct
{
    uint32_t PFlashBase;          
    uint32_t PFlashSize;          
    uint32_t DFlashBase;          
    uint32_t DFlashSize;          
    uint32_t EERAMBase;           
    uint32_t EEESize;             
    flash_callback_t CallBack;    
} flash_ssd_config_t;

typedef struct
{
    uint8_t brownOutCode;               
    uint16_t numOfRecordReqMaintain;    
    uint16_t sectorEraseCount;          
} flash_eeprom_status_t;


#if defined(__cplusplus)
extern "C" {
#endif


status_t FLASH_DRV_Init(const flash_user_config_t * const pUserConf,
                        flash_ssd_config_t * const pSSDConfig);

void FLASH_DRV_GetPFlashProtection(uint32_t * protectStatus);

status_t FLASH_DRV_SetPFlashProtection(uint32_t protectStatus);

void FLASH_DRV_GetSecurityState(uint8_t * securityState);

status_t FLASH_DRV_SecurityBypass(const flash_ssd_config_t * pSSDConfig,
                                  const uint8_t * keyBuffer);


status_t FLASH_DRV_EraseAllBlock(const flash_ssd_config_t * pSSDConfig);

status_t FLASH_DRV_VerifyAllBlock(const flash_ssd_config_t * pSSDConfig,
                                  uint8_t marginLevel);

status_t FLASH_DRV_EraseSector(const flash_ssd_config_t * pSSDConfig,
                               uint32_t dest,
                               uint32_t size);

status_t FLASH_DRV_VerifySection(const flash_ssd_config_t * pSSDConfig,
                                 uint32_t dest,
                                 uint16_t number,
                                 uint8_t marginLevel);

void FLASH_DRV_EraseSuspend(void);

void FLASH_DRV_EraseResume(void);

status_t FLASH_DRV_ReadOnce(const flash_ssd_config_t * pSSDConfig,
                            uint8_t recordIndex,
                            uint8_t * pDataArray);

status_t FLASH_DRV_ProgramOnce(const flash_ssd_config_t * pSSDConfig,
                               uint8_t recordIndex,
                               const uint8_t * pDataArray);

#if FEATURE_FLS_HAS_READ_RESOURCE_CMD
status_t FLASH_DRV_ReadResource(const flash_ssd_config_t * pSSDConfig,
                                uint32_t dest,
                                uint8_t * pDataArray,
                                uint8_t resourceSelectCode);
#endif

status_t FLASH_DRV_Program(const flash_ssd_config_t * pSSDConfig,
                           uint32_t dest,
                           uint32_t size,
                           const uint8_t * pData);

status_t FLASH_DRV_ProgramCheck(const flash_ssd_config_t * pSSDConfig,
                                uint32_t dest,
                                uint32_t size,
                                const uint8_t * pExpectedData,
                                uint32_t * pFailAddr,
                                uint8_t marginLevel);

status_t FLASH_DRV_CheckSum(const flash_ssd_config_t * pSSDConfig,
                            uint32_t dest,
                            uint32_t size,
                            uint32_t * pSum);

#if FEATURE_FLS_HAS_PROGRAM_SECTION_CMD
status_t FLASH_DRV_ProgramSection(const flash_ssd_config_t * pSSDConfig,
                                  uint32_t dest,
                                  uint16_t number);
#endif

#if FEATURE_FLS_HAS_ERASE_BLOCK_CMD
status_t FLASH_DRV_EraseBlock(const flash_ssd_config_t * pSSDConfig,
                              uint32_t dest);
#endif

#if FEATURE_FLS_HAS_READ_1S_BLOCK_CMD
status_t FLASH_DRV_VerifyBlock(const flash_ssd_config_t * pSSDConfig,
                               uint32_t dest,
                               uint8_t marginLevel);
#endif

#if FEATURE_FLS_HAS_FLEX_NVM
status_t FLASH_DRV_GetEERAMProtection(uint8_t * protectStatus);

status_t FLASH_DRV_SetEERAMProtection(uint8_t protectStatus);

status_t FLASH_DRV_SetFlexRamFunction(const flash_ssd_config_t * pSSDConfig,
                                      flash_flexRam_function_control_code_t flexRamFuncCode,
                                      uint16_t byteOfQuickWrite,
                                      flash_eeprom_status_t * const pEEPROMStatus);

status_t FLASH_DRV_EEEWrite(const flash_ssd_config_t * pSSDConfig,
                            uint32_t dest,
                            uint32_t size,
                            const uint8_t * pData);

status_t FLASH_DRV_DEFlashPartition(const flash_ssd_config_t * pSSDConfig,
                                    uint8_t uEEEDataSizeCode,
                                    uint8_t uDEPartitionCode,
                                    uint8_t uCSEcKeySize,
                                    bool uSFE,
                                    bool flexRamEnableLoadEEEData);

status_t FLASH_DRV_GetDFlashProtection(const flash_ssd_config_t * pSSDConfig,
                                       uint8_t * protectStatus);

status_t FLASH_DRV_SetDFlashProtection(const flash_ssd_config_t * pSSDConfig,
                                       uint8_t protectStatus);
#endif 

#if FEATURE_FLS_HAS_PF_BLOCK_SWAP
status_t FLASH_DRV_PFlashSwap(const flash_ssd_config_t * pSSDConfig,
                              uint32_t addr,
                              flash_swap_callback_t pSwapCallback);

status_t FLASH_DRV_PFlashSwapCtl(const flash_ssd_config_t * pSSDConfig,
                                 uint32_t addr,
                                 uint8_t swapcmd,
                                 uint8_t * pCurrentSwapMode,
                                 uint8_t * pCurrentSwapBlockStatus,
                                 uint8_t * pNextSwapBlockStatus);

#endif 

#if FEATURE_FLS_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD
status_t FLASH_DRV_EraseAllBlockUnsecure(const flash_ssd_config_t * pSSDConfig);
#endif 

status_t FLASH_DRV_EnableCmdCompleteInterupt(void);

void FLASH_DRV_DisableCmdCompleteInterupt(void);

static inline bool FLASH_DRV_GetCmdCompleteFlag(void)
{
    return (((FTFx_FSTAT & FTFx_FSTAT_CCIF_MASK) >> FTFx_FSTAT_CCIF_SHIFT) != 0U);
}

status_t FLASH_DRV_EnableReadColisionInterupt(void);

void FLASH_DRV_DisableReadColisionInterupt(void);

static inline bool FLASH_DRV_GetReadColisionFlag(void)
{
    return (((FTFx_FSTAT & FTFx_FSTAT_RDCOLERR_MASK) >> FTFx_FSTAT_RDCOLERR_SHIFT) != 0U);
}

static inline void FLASH_DRV_ClearReadColisionFlag(void)
{
    FTFx_FSTAT = FTFx_FSTAT_RDCOLERR_MASK;
}

#if FEATURE_FLS_HAS_DETECT_ECC_ERROR
status_t FLASH_DRV_EnableDoubleBitFaultInterupt(void);

void FLASH_DRV_DisableDoubleBitFaultInterupt(void);

static inline bool FLASH_DRV_GetDoubleBitFaultFlag(void)
{
    return (((FTFx_FERSTAT & FTFx_FERSTAT_DFDIF_MASK) >> FTFx_FERSTAT_DFDIF_SHIFT) != 0U);
}

static inline void FLASH_DRV_ClearDoubleBitFaultFlag(void)
{
    FTFx_FERSTAT = FTFx_FERSTAT_DFDIF_MASK;
}

static inline void FLASH_DRV_ForceDoubleBitFaultDetectCmd(bool isEnable)
{
    if (true == isEnable)
    {
        FTFx_FERCNFG |= FTFx_FERCNFG_FDFD_MASK;
    }
    else
    {
        FTFx_FERCNFG &= (uint8_t)(~FTFx_FERCNFG_FDFD_MASK);
    }
}
#endif 

void FLASH_DRV_GetDefaultConfig(flash_user_config_t * const config);

#if defined(__cplusplus)
}
#endif


#endif 

