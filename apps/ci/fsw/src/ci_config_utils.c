
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "ci_config_utils.h"

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/
extern CI_AppData_t  CI_AppData;

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
/* Initialize Config Table                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 CI_InitTbls()
{
    int32  iStatus=0;

    /* Register Config table */
    iStatus = CFE_TBL_Register(&CI_AppData.ConfigTblHdl,
                               CI_CONFIG_TABLENAME,
                               (sizeof(CI_ConfigTblEntry_t) * CI_CONFIG_TABLE_MAX_ENTRIES),
                               CFE_TBL_OPT_DEFAULT,
                               CI_ValidateConfigTbl);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(CI_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to register Config table (0x%08X)",
                                 (unsigned int)iStatus);
        goto CI_InitTbls_Exit_Tag;
    }

    /* Register Timeout dump table */
	iStatus = CFE_TBL_Register(&CI_AppData.TimeoutTblHdl,
							   CI_TIMEOUT_TABLENAME,
							   (sizeof(CI_TimeoutTblEntry_t) * CI_CONFIG_TABLE_MAX_ENTRIES),
							   CFE_TBL_OPT_USR_DEF_ADDR,
							   0);
	if (iStatus != CFE_SUCCESS)
	{
		(void) CFE_EVS_SendEvent(CI_INIT_ERR_EID, CFE_EVS_ERROR,
								 "Failed to register Timeout table (0x%08X)",
								 (unsigned int)iStatus);
		goto CI_InitTbls_Exit_Tag;
	}

    /* Load Config table file */
    iStatus = CFE_TBL_Load(CI_AppData.ConfigTblHdl,
                           CFE_TBL_SRC_FILE,
                           CI_CONFIG_TABLE_FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(CI_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to load Config Table (0x%08X)",
                                 (unsigned int)iStatus);
        goto CI_InitTbls_Exit_Tag;
    }

    /* Load Timeout table file */
	iStatus = CFE_TBL_Load(CI_AppData.TimeoutTblHdl,
						   CFE_TBL_SRC_ADDRESS,
						   &CI_AppData.TimeoutTbl);
	if (iStatus != CFE_SUCCESS)
	{
		(void) CFE_EVS_SendEvent(CI_INIT_ERR_EID, CFE_EVS_ERROR,
								 "Failed to load Timeout Table (0x%08X)",
								 (unsigned int)iStatus);
		goto CI_InitTbls_Exit_Tag;
	}

    iStatus = CI_AcquireConfigPointers();

CI_InitTbls_Exit_Tag:
    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Validate Config Table                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 CI_ValidateConfigTbl(void* ConfigTblPtr)
{
    int32  iStatus=0;
    CI_ConfigTblEntry_t* CI_ConfigTblPtr = (CI_ConfigTblEntry_t*)(ConfigTblPtr);

    if (ConfigTblPtr == NULL)
    {
        iStatus = -1;
        goto CI_ValidateConfigTbl_Exit_Tag;
    }

    /* TODO:  Add code to validate new data values here.
    **
    ** Examples:
    ** if (CI_ConfigTblPtr->iParam <= 16) {
    **   (void) CFE_EVS_SendEvent(CI_CONFIG_TABLE_INF_EID, CFE_EVS_ERROR,
     *                         "Invalid value for Config parameter sParam (%d)",
    **                         CI_ConfigTblPtr->iParam);
    ** }
    **/

CI_ValidateConfigTbl_Exit_Tag:
    return (iStatus);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process New Config Table                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void CI_ProcessNewConfigTbl()
{
    /* TODO:  Add code to set new Config parameters with new values here.
    **
    ** Examples:
    **
    **    CI_AppData.latest_sParam = CI_AppData.ConfigTblPtr->sParam;
    **    CI_AppData.latest_fParam = CI.AppData.ConfigTblPtr->fParam;
    */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process New Timeout Table                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void CI_ProcessNewTimeoutTbl()
{
    /* TODO:  Add code to set new Config parameters with new values here.
    **
    ** Examples:
    **
    **    CI_AppData.latest_sParam = CI_AppData.ConfigTblPtr->sParam;
    **    CI_AppData.latest_fParam = CI.AppData.ConfigTblPtr->fParam;
    */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Acquire Conifg Pointers                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 CI_AcquireConfigPointers(void)
{
	 int32 iStatus = CFE_SUCCESS;

	/*
	** Release the table
	*/
	/* TODO: This return value can indicate success, error, or that the info has been
	 * updated.  We ignore this return value in favor of checking CFE_TBL_Manage(), but
	 * be sure this is the behavior you want. */
	(void) CFE_TBL_ReleaseAddress(CI_AppData.ConfigTblHdl);
	(void) CFE_TBL_ReleaseAddress(CI_AppData.TimeoutTblHdl);

	/*
	** Manage the tables
	*/
	iStatus = CFE_TBL_Manage(CI_AppData.ConfigTblHdl);
	if ((iStatus != CFE_SUCCESS) && (iStatus != CFE_TBL_INFO_UPDATED))
	{
		(void) CFE_EVS_SendEvent(CI_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
								 "Failed to manage Config table (0x%08X)",
								 (unsigned int)iStatus);
		goto CI_AcquireConfigPointers_Exit_Tag;
	}

	iStatus = CFE_TBL_Manage(CI_AppData.TimeoutTblHdl);
	if ((iStatus != CFE_SUCCESS) && (iStatus != CFE_TBL_INFO_UPDATED))
	{
		(void) CFE_EVS_SendEvent(CI_TIMEOUT_TABLE_ERR_EID, CFE_EVS_ERROR,
								 "Failed to manage Timeout table (0x%08X)",
								 (unsigned int)iStatus);
		goto CI_AcquireConfigPointers_Exit_Tag;
	}

	/*
	** Get a pointer to the tables
	*/
	iStatus = CFE_TBL_GetAddress((void*)&CI_AppData.ConfigTblPtr,
								 CI_AppData.ConfigTblHdl);
	if (iStatus == CFE_TBL_INFO_UPDATED)
	{
		CI_ProcessNewConfigTbl();
		iStatus = CFE_SUCCESS;
	}
	else if(iStatus != CFE_SUCCESS)
	{
		CI_AppData.ConfigTblPtr = 0;
		(void) CFE_EVS_SendEvent(CI_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
								 "Failed to get Config table's address (0x%08X)",
								 (unsigned int)iStatus);
	}

	iStatus = CFE_TBL_GetAddress((void*)&CI_AppData.TimeoutTbl,
									 CI_AppData.TimeoutTblHdl);
	if (iStatus == CFE_TBL_INFO_UPDATED)
	{
		CI_ProcessNewTimeoutTbl();
		iStatus = CFE_SUCCESS;
	}
	else if(iStatus != CFE_SUCCESS)
	{
		(void) CFE_EVS_SendEvent(CI_TIMEOUT_TABLE_ERR_EID, CFE_EVS_ERROR,
								 "Failed to get Timeout table's address (0x%08X)",
								 (unsigned int)iStatus);
	}

CI_AcquireConfigPointers_Exit_Tag:
    return (iStatus);

} /* End of CI_AcquirePointers */

/************************/
/*  End of File Comment */
/************************/
    
