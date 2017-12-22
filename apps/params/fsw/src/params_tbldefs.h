    
#ifndef PARAMS_TBLDEFS_H
#define PARAMS_TBLDEFS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "params_platform_cfg.h"
#include "params_msg.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/
/**
 * \brief Defines the number of entries in the table
 */
#define PARAMS_PARAM_TABLE_MAX_ENTRIES  (15)

/**
 * \brief Defines the table identification name used for table registration.
 */
#define PARAMS_PARAM_TABLENAME          ("PARAM_TBL")

/**
 * \brief Defines the table file name used for table registration.
 */
#define PARAMS_CDS_TABLENAME  ("params_CdsTbl")

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** \brief Definition for a single config table entry */
typedef struct
{
	uint8 enabled;
	uint8 vehicle_id;
	uint8 component_id;
	PARAMS_ParamData_t param_data;
} PARAMS_ParamTblData_t;

/** \brief Definition for a single config table entry */
typedef struct
{
    uint8                   tableID;
    PARAMS_ParamTblData_t     params[PARAMS_PARAM_TABLE_MAX_ENTRIES];
} PARAMS_ParamsTblEntry_t;


/** \brief Definition for Critical Data Storage (CDS) table entry */
typedef struct
{
    int32  iParam;

    /* TODO:  Add type declaration for CDS data here. */
} PARAMS_CdsTbl_t;

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

#endif /* PARAMS_TBLDEFS_H */

/************************/
/*  End of File Comment */
/************************/
