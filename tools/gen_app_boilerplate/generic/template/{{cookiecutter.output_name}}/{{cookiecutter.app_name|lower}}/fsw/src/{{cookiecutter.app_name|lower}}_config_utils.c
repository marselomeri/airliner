
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "{{cookiecutter.app_name|lower}}_config_utils.h"

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
/* Initialize Config Table                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 {{cookiecutter.app_name}}_InitConfigTbl()
{
    int32  iStatus=0;

    /* Register Config table */
    iStatus = CFE_TBL_Register(&{{cookiecutter.app_name}}_AppData.ConfigTblHdl,
                               {{cookiecutter.app_name}}_CONFIG_TABLENAME,
                               (sizeof({{cookiecutter.app_name}}_ConfigTblEntry_t) * {{cookiecutter.app_name}}_CONFIG_TABLE_MAX_ENTRIES),
                               CFE_TBL_OPT_DEFAULT,
                               {{cookiecutter.app_name}}_ValidateConfigTbl);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, a critical table could return another nominal code.  If this table is
         * made critical this logic would have to change. */
        (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to register Config table (0x%08X)",
                                 (unsigned int)iStatus);
        goto {{cookiecutter.app_name}}_InitConfigTbl_Exit_Tag;
    }

    /* Load Config table file */
    iStatus = CFE_TBL_Load({{cookiecutter.app_name}}_AppData.ConfigTblHdl,
                           CFE_TBL_SRC_FILE,
                           {{cookiecutter.app_name}}_CONFIG_TABLE_FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, CFE_SUCCESS is for a successful full table load.  If a partial table
           load is desired then this logic would have to change. */
        (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to load Config Table (0x%08X)",
                                 (unsigned int)iStatus);
        goto {{cookiecutter.app_name}}_InitConfigTbl_Exit_Tag;
    }

    iStatus = {{cookiecutter.app_name}}_AcquireConfigPointers();

{{cookiecutter.app_name}}_InitConfigTbl_Exit_Tag:
    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Validate Config Table                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 {{cookiecutter.app_name}}_ValidateConfigTbl(void* ConfigTblPtr)
{
    int32  iStatus=0;
    {{cookiecutter.app_name}}_ConfigTblEntry_t* {{cookiecutter.app_name}}_ConfigTblPtr = ({{cookiecutter.app_name}}_ConfigTblEntry_t*)(ConfigTblPtr);

    if (ConfigTblPtr == NULL)
    {
        iStatus = -1;
        goto {{cookiecutter.app_name}}_ValidateConfigTbl_Exit_Tag;
    }

    /* TODO:  Add code to validate new data values here.
    **
    ** Examples:
    ** if ({{cookiecutter.app_name}}_ConfigTblPtr->iParam <= 16) {
    **   (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_CONFIG_TABLE_INF_EID, CFE_EVS_ERROR,
     *                         "Invalid value for Config parameter sParam (%d)",
    **                         {{cookiecutter.app_name}}_ConfigTblPtr->iParam);
    ** }
    **/

{{cookiecutter.app_name}}_ValidateConfigTbl_Exit_Tag:
    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process New Config Table                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void {{cookiecutter.app_name}}_ProcessNewConfigTbl()
{
    /* TODO:  Add code to set new Config parameters with new values here.
    **
    ** Examples:
    **
    **    {{cookiecutter.app_name}}_AppData.latest_sParam = {{cookiecutter.app_name}}_AppData.ConfigTblPtr->sParam;
    **    {{cookiecutter.app_name}}_AppData.latest_fParam = {{cookiecutter.app_name}}.AppData.ConfigTblPtr->fParam;
    */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Acquire Conifg Pointers                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 {{cookiecutter.app_name}}_AcquireConfigPointers(void)
{
    int32 iStatus = CFE_SUCCESS;

    /*
    ** Release the table
    */
    /* TODO: This return value can indicate success, error, or that the info has been 
     * updated.  We ignore this return value in favor of checking CFE_TBL_Manage(), but
     * be sure this is the behavior you want. */
    (void) CFE_TBL_ReleaseAddress({{cookiecutter.app_name}}_AppData.ConfigTblHdl);

    /*
    ** Manage the table
    */
    iStatus = CFE_TBL_Manage({{cookiecutter.app_name}}_AppData.ConfigTblHdl);
    if ((iStatus != CFE_SUCCESS) && (iStatus != CFE_TBL_INFO_UPDATED))
    {
        (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to manage Config table (0x%08X)",
                                 (unsigned int)iStatus);
        goto {{cookiecutter.app_name}}_AcquireConfigPointers_Exit_Tag;
    }

    /*
    ** Get a pointer to the table
    */
    iStatus = CFE_TBL_GetAddress((void*)&{{cookiecutter.app_name}}_AppData.ConfigTblPtr,
                                 {{cookiecutter.app_name}}_AppData.ConfigTblHdl);
    if (iStatus == CFE_TBL_INFO_UPDATED)
    {
        {{cookiecutter.app_name}}_ProcessNewConfigTbl();
        iStatus = CFE_SUCCESS;
    }
    else if(iStatus != CFE_SUCCESS)
    {
	{{cookiecutter.app_name}}_AppData.ConfigTblPtr = 0;
        (void) CFE_EVS_SendEvent({{cookiecutter.app_name}}_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to get Config table's address (0x%08X)",
                                 (unsigned int)iStatus);
    }

{{cookiecutter.app_name}}_AcquireConfigPointers_Exit_Tag:
    return (iStatus);

} /* End of {{cookiecutter.app_name}}_AcquirePointers */

/************************/
/*  End of File Comment */
/************************/
    
