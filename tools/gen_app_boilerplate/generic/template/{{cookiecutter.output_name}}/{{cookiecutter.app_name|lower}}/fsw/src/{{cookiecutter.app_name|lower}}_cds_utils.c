
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include <string.h>
#include "{{cookiecutter.app_name|lower}}_app.h"
#include "{{cookiecutter.app_name|lower}}_cds_utils.h"

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/
extern {{cookiecutter.app_name}}_AppData_t  {{cookiecutter.app_name}}_AppData;

/************************************************************************
** Global Variables
*************************************************************************/

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Function Prototypes
*************************************************************************/

/************************************************************************
** Function Definitions
*************************************************************************/


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize CDS Tables                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 {{cookiecutter.app_name}}_InitCdsTbl()
{
    int32  iStatus=0;
    int32  iResetType=0;
    uint32 uiResetSubType=0;

    /* Only clear CDS table when it's a PowerOn reset, and not a Processor reset */
    iResetType = CFE_ES_GetResetType(&uiResetSubType);
    if (iResetType == CFE_ES_POWERON_RESET)
    {
        memset((void*)&{{cookiecutter.app_name}}_AppData.CdsTbl, 0x00, sizeof({{cookiecutter.app_name}}_CdsTbl_t));
    }

    /* Register and manage CDS table */
    iStatus = CFE_ES_RegisterCDS(&{{cookiecutter.app_name}}_AppData.CdsTblHdl, sizeof({{cookiecutter.app_name}}_CdsTbl_t),
                                 {{cookiecutter.app_name}}_CDS_TABLENAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Setup initial content of CDS table */
        iStatus = CFE_ES_CopyToCDS({{cookiecutter.app_name}}_AppData.CdsTblHdl, &{{cookiecutter.app_name}}_AppData.CdsTbl);
        if (iStatus == CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_CDS_INF_EID, CFE_EVS_INFORMATION,
                                     "Successfully setup CDS");
        }
        else
        {
            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "Failed to setup CDS");
        }
    }
    else if (iStatus == CFE_ES_CDS_ALREADY_EXISTS)
    {
        /* If one already exists, get a copy of its current content */
        memset((void*)&{{cookiecutter.app_name}}_AppData.CdsTbl, 0x00, sizeof({{cookiecutter.app_name}}_CdsTbl_t));
        iStatus = CFE_ES_RestoreFromCDS(&{{cookiecutter.app_name}}_AppData.CdsTbl, {{cookiecutter.app_name}}_AppData.CdsTblHdl);
        if (iStatus == CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_CDS_INF_EID, CFE_EVS_INFORMATION,
                                     "Successfully restored data from CDS");
        }
        else
        {
            (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_INIT_ERR_EID, CFE_EVS_ERROR,
                                     "Failed to restore data from CDS");
            memset((void*)&{{cookiecutter.app_name}}_AppData.CdsTbl, 0x00, sizeof({{cookiecutter.app_name}}_CdsTbl_t));
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create CDS (0x%08X)", (unsigned int)iStatus);
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Update CDS Tables                                               */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void {{cookiecutter.app_name}}_UpdateCdsTbl()
{
    /* TODO:  Add code to update values in CDS table here */
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Save CDS Tables                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void {{cookiecutter.app_name}}_SaveCdsTbl()
{
    /* TODO This return value is not checked. Developer should decide what to do here
       in case of failure or should add a return value for higher-level logic to handle. */
    CFE_ES_CopyToCDS({{cookiecutter.app_name}}_AppData.CdsTblHdl, &{{cookiecutter.app_name}}_AppData.CdsTbl);
}

/************************/
/*  End of File Comment */
/************************/
    
