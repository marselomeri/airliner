    
#ifndef PMC_CONFIG_UTILS_H
#define PMC_CONFIG_UTILS_H

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
#include "pmc_app.h"

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
/** \brief Init PMC Config table
**
**  \par Description
**       This function initializes PMC's Config table
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \retstmt Return codes from #CFE_TBL_Register          \endcode
**  \retstmt Return codes from #CFE_TBL_Load              \endcode
**  \retstmt Return codes from #PMC_AcquireConfigPointers \endcode
**  \endreturns
**
*************************************************************************/
int32  PMC_InitConfigTbl(void);

/************************************************************************/
/** \brief Validate PMC Config table
**
**  \par Description
**       This function validates PMC's Config table
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \endreturns
**
*************************************************************************/
int32  PMC_ValidatePwmCfgTbl(void*);

int32  PMC_ValidateMixerCfgTbl(void*);

/************************************************************************/
/** \brief Obtain PMC Config Table Data Pointer
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
int32 PMC_AcquireConfigPointers(void);

/************************************************************************/
/** \brief Process new PMC Config table
**
**  \par Description
**       This function processes PMC's new Config table
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
void   PMC_ProcessNewPwmConfigTbl(void);

void   PMC_ProcessNewMixerConfigTbl(void);


#ifdef __cplusplus
}
#endif

#endif /* PMC_CONFIG_UTILS_H */

/************************/
/*  End of File Comment */
/************************/
    
