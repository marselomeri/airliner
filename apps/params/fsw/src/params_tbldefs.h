    
#ifndef PARAMS_TBLDEFS_H
#define PARAMS_TBLDEFS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/
/**
 * \brief Defines the number of entries in the table
 */
#define PARAMS_PARAM_TABLE_MAX_ENTRIES  (1)

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
    int32  iParam;

    /* TODO:  Add type declaration for config parameters here.
    **
    ** Examples:
    **    int8/char            cParam;
    **    int8/char            cParams[16];
    **    uint8/unsigned char  ucParam;
    **    uint8/unsigned char  ucParams[16];
    **
    **    int16   sParam;
    **    int16   sParams[8];
    **    uint16  usParam;
    **    uint16  usParams[8];
    **
    **    int32   iParam;
    **    int32   iParams[5];
    **    uint32  uiParam;
    **    uint32  uiParams[5];
    **
    **    float  fParam;
    **    float  fParams[3];
    **
    **    double  dParam;
    **    double  dParams[3];
    */
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
