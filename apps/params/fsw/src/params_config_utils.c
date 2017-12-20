
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "params_config_utils.h"

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/
extern PARAMS_AppData_t  PARAMS_AppData;

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

int32 PARAMS_InitConfigTbl()
{
    int32  iStatus=0;

    /* Register Config table */
    iStatus = CFE_TBL_Register(&PARAMS_AppData.ConfigTblHdl,
                               PARAMS_PARAM_TABLENAME,
                               (sizeof(PARAMS_ParamsTblEntry_t) * PARAMS_PARAM_TABLE_MAX_ENTRIES),
                               CFE_TBL_OPT_DEFAULT,
                               PARAMS_ValidateConfigTbl);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, a critical table could return another nominal code.  If this table is
         * made critical this logic would have to change. */
        (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to register Config table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PARAMS_InitConfigTbl_Exit_Tag;
    }

    /* Load Config table file */
    iStatus = CFE_TBL_Load(PARAMS_AppData.ConfigTblHdl,
                           CFE_TBL_SRC_FILE,
                           PARAMS_PARAM_TABLE_FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, CFE_SUCCESS is for a successful full table load.  If a partial table
           load is desired then this logic would have to change. */
        (void) CFE_EVS_SendEvent(PARAMS_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to load Config Table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PARAMS_InitConfigTbl_Exit_Tag;
    }

    iStatus = PARAMS_AcquireConfigPointers();

PARAMS_InitConfigTbl_Exit_Tag:
    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Validate Config Table                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PARAMS_ValidateConfigTbl(void* ConfigTblPtr)
{
    int32  iStatus=0;
    PARAMS_ParamsTblEntry_t* PARAMS_ConfigTblPtr = (PARAMS_ParamsTblEntry_t*)(ConfigTblPtr);

    if (ConfigTblPtr == NULL)
    {
        iStatus = -1;
        goto PARAMS_ValidateConfigTbl_Exit_Tag;
    }

    /* TODO:  Add code to validate new data values here.
    **
    ** Examples:
    ** if (PARAMS_ConfigTblPtr->iParam <= 16) {
    **   (void) CFE_EVS_SendEvent(PARAMS_CONFIG_TABLE_INF_EID, CFE_EVS_ERROR,
     *                         "Invalid value for Config parameter sParam (%d)",
    **                         PARAMS_ConfigTblPtr->iParam);
    ** }
    **/

PARAMS_ValidateConfigTbl_Exit_Tag:
    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process New Config Table                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PARAMS_ProcessNewConfigTbl()
{
    /* TODO:  Add code to set new Config parameters with new values here.
    **
    ** Examples:
    **
    **    PARAMS_AppData.latest_sParam = PARAMS_AppData.ConfigTblPtr->sParam;
    **    PARAMS_AppData.latest_fParam = PARAMS.AppData.ConfigTblPtr->fParam;
    */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Acquire Conifg Pointers                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 PARAMS_AcquireConfigPointers(void)
{
    int32 iStatus = CFE_SUCCESS;

    /*
    ** Release the table
    */
    /* TODO: This return value can indicate success, error, or that the info has been 
     * updated.  We ignore this return value in favor of checking CFE_TBL_Manage(), but
     * be sure this is the behavior you want. */
    (void) CFE_TBL_ReleaseAddress(PARAMS_AppData.ConfigTblHdl);

    /*
    ** Manage the table
    */
    iStatus = CFE_TBL_Manage(PARAMS_AppData.ConfigTblHdl);
    if ((iStatus != CFE_SUCCESS) && (iStatus != CFE_TBL_INFO_UPDATED))
    {
        (void) CFE_EVS_SendEvent(PARAMS_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to manage Config table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PARAMS_AcquireConfigPointers_Exit_Tag;
    }

    /*
    ** Get a pointer to the table
    */
    iStatus = CFE_TBL_GetAddress((void*)&PARAMS_AppData.ConfigTblPtr,
                                 PARAMS_AppData.ConfigTblHdl);
    if (iStatus == CFE_TBL_INFO_UPDATED)
    {
        PARAMS_ProcessNewConfigTbl();
        iStatus = CFE_SUCCESS;
    }
    else if(iStatus != CFE_SUCCESS)
    {
	PARAMS_AppData.ConfigTblPtr = 0;
        (void) CFE_EVS_SendEvent(PARAMS_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to get Config table's address (0x%08X)",
                                 (unsigned int)iStatus);
    }

PARAMS_AcquireConfigPointers_Exit_Tag:
    return (iStatus);

} /* End of PARAMS_AcquirePointers */

/************************/
/*  End of File Comment */
/************************/
    
