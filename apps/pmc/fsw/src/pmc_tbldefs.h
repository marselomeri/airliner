    
#ifndef PMC_TBLDEFS_H
#define PMC_TBLDEFS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "cfe.h"
#include "pmc_platform_cfg.h"

/************************************************************************
** Local Defines
*************************************************************************/
/**
 * \brief Defines the table identification name used for table registration.
 */
#define PMC_PWM_CONFIG_TABLENAME ("PWMCFG_TBL")
#define PMC_MIXER_CONFIG_TABLENAME ("MIXERCFG_TBL")

/**
 * \brief Defines the table file name used for table registration.
 */
#define PMC_CDS_TABLENAME  ("pmc_CdsTbl")

/** \brief Definition for a single config table entry */
typedef struct
{
    int32  PwmDisarmed;
    int32  PwmMin;
    int32  PwmMax;
} PMC_PwmConfigTbl_t;


#ifdef __cplusplus
}
#endif

#endif /* PMC_TBLDEFS_H */

/************************/
/*  End of File Comment */
/************************/
