    
#ifndef {{cookiecutter.app_name}}_CONFIG_UTILS_H
#define {{cookiecutter.app_name}}_CONFIG_UTILS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "{{cookiecutter.app_name|lower}}_app.h"

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
/** \brief Init {{cookiecutter.app_name}} Config table
**
**  \par Description
**       This function initializes {{cookiecutter.app_name}}'s Config table
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \retstmt Return codes from #CFE_TBL_Register          \endcode
**  \retstmt Return codes from #CFE_TBL_Load              \endcode
**  \retstmt Return codes from #{{cookiecutter.app_name}}_AcquireConfigPointers \endcode
**  \endreturns
**
*************************************************************************/
int32  {{cookiecutter.app_name}}_InitConfigTbl(void);

/************************************************************************/
/** \brief Validate {{cookiecutter.app_name}} Config table
**
**  \par Description
**       This function validates {{cookiecutter.app_name}}'s Config table
**
**  \par Assumptions, External Events, and Notes:
**       None
**
**  \returns
**  \retcode #CFE_SUCCESS  \retdesc \copydoc CFE_SUCCESS  \endcode
**  \endreturns
**
*************************************************************************/
int32  {{cookiecutter.app_name}}_ValidateConfigTbl(void*);

/************************************************************************/
/** \brief Obtain {{cookiecutter.app_name}} Config Table Data Pointer
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
int32 {{cookiecutter.app_name}}_AcquireConfigPointers(void);

/************************************************************************/
/** \brief Process new {{cookiecutter.app_name}} Config table
**
**  \par Description
**       This function processes {{cookiecutter.app_name}}'s new Config table
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
void   {{cookiecutter.app_name}}_ProcessNewConfigTbl(void);


#ifdef __cplusplus
}
#endif

#endif /* {{cookiecutter.app_name}}_CONFIG_UTILS_H */

/************************/
/*  End of File Comment */
/************************/
    
