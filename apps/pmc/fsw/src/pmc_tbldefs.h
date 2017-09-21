    
#ifndef PMC_TBLDEFS_H
#define PMC_TBLDEFS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "pmc_platform_cfg.h"
#include "mixer.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/
/**
 * \brief Defines the number of entries in the table
 */
#define PMC_CONFIG_TABLE_MAX_ENTRIES  (1)

/**
 * \brief Defines the table identification name used for table registration.
 */
#define PMC_CONFIG_TABLENAME ("CONFIG_TBL")

/**
 * \brief Defines the table file name used for table registration.
 */
#define PMC_CDS_TABLENAME  ("pmc_CdsTbl")

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** \brief Definition for a single config table entry */
typedef struct
{
    int32  PwmDisarmed;
    int32  PwmMin;
    int32  PwmMax;
    float  RollScale;
    float  PitchScale;
    float  YawScale;
    float  IdleSpeed;
    uint32 RotorCount;
    MIXER_RotorConfig_t RotorConfig[PMC_MAX_ROTOR_COUNT];
} PMC_ConfigTblEntry_t;


/** \brief Definition for Critical Data Storage (CDS) table entry */
typedef struct
{
    int32  iParam;

    /* TODO:  Add type declaration for CDS data here. */
} PMC_CdsTbl_t;

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Prototypes
*************************************************************************/


#ifdef __cplusplus
}
#endif

#endif /* PMC_TBLDEFS_H */

/************************/
/*  End of File Comment */
/************************/
