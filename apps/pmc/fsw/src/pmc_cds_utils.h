
#ifndef PMC_CDS_UTILS_H
#define PMC_CDS_UTILS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "pmc_tbldefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

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

/************************************************************************/
/** \brief Init PMC CDS tables
**
**  \par Description
**       This function initializes PMC's CDS tables
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS \endcode
**  \retstmt Return codes from #CFE_ES_RegisterCDS       \endcode
**  \retstmt Return codes from #CFE_ES_CopyToCDS         \endcode
**  \endreturns
**
*************************************************************************/
int32  PMC_InitCdsTbl(void);

/************************************************************************/
/** \brief Update PMC CDS tables
**
**  \par Description
**       This function updates PMC's CDS tables
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void   PMC_UpdateCdsTbl(void);

/************************************************************************/
/** \brief Save PMC CDS tables
**
**  \par Description
**       This function saves PMC's CDS tables
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void   PMC_SaveCdsTbl(void);


#ifdef __cplusplus
}
#endif
 
#endif /* PMC_CDS_UTILS_H */

/************************/
/*  End of File Comment */
/************************/
    
