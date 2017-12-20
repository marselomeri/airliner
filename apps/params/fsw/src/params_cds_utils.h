
#ifndef PARAMS_CDS_UTILS_H
#define PARAMS_CDS_UTILS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "params_tbldefs.h"

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
/** \brief Init PARAMS CDS tables
**
**  \par Description
**       This function initializes PARAMS's CDS tables
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
int32  PARAMS_InitCdsTbl(void);

/************************************************************************/
/** \brief Update PARAMS CDS tables
**
**  \par Description
**       This function updates PARAMS's CDS tables
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void   PARAMS_UpdateCdsTbl(void);

/************************************************************************/
/** \brief Save PARAMS CDS tables
**
**  \par Description
**       This function saves PARAMS's CDS tables
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void   PARAMS_SaveCdsTbl(void);


#ifdef __cplusplus
}
#endif
 
#endif /* PARAMS_CDS_UTILS_H */

/************************/
/*  End of File Comment */
/************************/
    
