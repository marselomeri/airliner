    
#ifndef PARAMS_CONFIG_UTILS_H
#define PARAMS_CONFIG_UTILS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "params_app.h"

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
/** \brief Init PARAMS Config table
**
**  \par Description
**       This function initializes PARAMS's Config table
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \retstmt Return codes from #CFE_TBL_Register          \endcode
**  \retstmt Return codes from #CFE_TBL_Load              \endcode
**  \retstmt Return codes from #PARAMS_AcquireConfigPointers \endcode
**  \endreturns
**
*************************************************************************/
int32  PARAMS_InitConfigTbl(void);

/************************************************************************/
/** \brief Validate PARAMS Config table
**
**  \par Description
**       This function validates PARAMS's Config table
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \endreturns
**
*************************************************************************/
int32  PARAMS_ValidateConfigTbl(void*);

/************************************************************************/
/** \brief Obtain PARAMS Config Table Data Pointer
**
**  \par Description
**       This function manages the config table
**       and obtains a pointer to its data.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \endreturns
**
*************************************************************************/
int32 PARAMS_AcquireConfigPointers(void);

/************************************************************************/
/** \brief Process new PARAMS Config table
**
**  \par Description
**       This function processes PARAMS's new Config table
**       and set Config parameters with new values.
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \endreturns
**
*************************************************************************/
void   PARAMS_ProcessNewConfigTbl(void);


#ifdef __cplusplus
}
#endif

#endif /* PARAMS_CONFIG_UTILS_H */

/************************/
/*  End of File Comment */
/************************/
    
