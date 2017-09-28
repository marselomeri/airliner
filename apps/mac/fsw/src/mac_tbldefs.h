    
#ifndef MAC_TBLDEFS_H
#define MAC_TBLDEFS_H

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
#include "mac_platform_cfg.h"

/************************************************************************
** Local Defines
*************************************************************************/
/**
 * \brief Defines the number of entries in the table
 */
#define MAC_CONFIG_TABLE_MAX_ENTRIES  (1)

/**
 * \brief Defines the table identification name used for table registration.
 */
#define MAC_PWM_CONFIG_TABLENAME ("PWMCFG_TBL")
#define MAC_MIXER_CONFIG_TABLENAME ("MIXERCFG_TBL")

/**
 * \brief Defines the table file name used for table registration.
 */
#define MAC_CDS_TABLENAME  ("mac_CdsTbl")

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** \brief Definition for a single config table entry */
typedef struct
{
    int32  PwmDisarmed;
    int32  PwmMin;
    int32  PwmMax;
} MAC_PwmConfigTbl_t;


/** \brief Definition for Critical Data Storage (CDS) table entry */
typedef struct
{
    int32  iParam;

    /* TODO:  Add type declaration for CDS data here. */
} MAC_CdsTbl_t;

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

#endif /* MAC_TBLDEFS_H */

/************************/
/*  End of File Comment */
/************************/
