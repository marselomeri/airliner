
#ifndef {{cookiecutter.app_name}}_CDS_UTILS_H
#define {{cookiecutter.app_name}}_CDS_UTILS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "{{cookiecutter.app_name|lower}}_tbldefs.h"

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
/** \brief Init {{cookiecutter.app_name}} CDS tables
**
**  \par Description
**       This function initializes {{cookiecutter.app_name}}'s CDS tables
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
int32  {{cookiecutter.app_name}}_InitCdsTbl(void);

/************************************************************************/
/** \brief Update {{cookiecutter.app_name}} CDS tables
**
**  \par Description
**       This function updates {{cookiecutter.app_name}}'s CDS tables
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void   {{cookiecutter.app_name}}_UpdateCdsTbl(void);

/************************************************************************/
/** \brief Save {{cookiecutter.app_name}} CDS tables
**
**  \par Description
**       This function saves {{cookiecutter.app_name}}'s CDS tables
**
**  \par Assumptions, External Events, and Notes:
**       None
**
*************************************************************************/
void   {{cookiecutter.app_name}}_SaveCdsTbl(void);


#ifdef __cplusplus
}
#endif
 
#endif /* {{cookiecutter.app_name}}_CDS_UTILS_H */

/************************/
/*  End of File Comment */
/************************/
    
