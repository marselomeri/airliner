
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "pmc_config_utils.h"

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

int32 PMC::InitConfigTbl()
{
    int32  iStatus=0;

    /* Register Config table */
    iStatus = CFE_TBL_Register(&PwmConfigTblHdl,
                               PMC_PWM_CONFIG_TABLENAME,
                               (sizeof(PMC_PwmConfigTbl_t)),
                               CFE_TBL_OPT_DEFAULT,
							   PMC::ValidatePwmCfgTbl);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, a critical table could return another nominal code.  If this table is
         * made critical this logic would have to change. */
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to register PWM table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitConfigTbl_Exit_Tag;
    }

    /* Register Mixer table */
    iStatus = CFE_TBL_Register(&MixerConfigTblHdl,
                               PMC_MIXER_CONFIG_TABLENAME,
                               (sizeof(MultirotorMixer_ConfigTable_t)),
                               CFE_TBL_OPT_DEFAULT,
							   PMC::ValidateMixerCfgTbl);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, a critical table could return another nominal code.  If this table is
         * made critical this logic would have to change. */
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to register Mixer table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitConfigTbl_Exit_Tag;
    }

    /* Load Config table file */
    iStatus = CFE_TBL_Load(PwmConfigTblHdl,
                           CFE_TBL_SRC_FILE,
                           PMC_PWM_CONFIG_TABLE_FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, CFE_SUCCESS is for a successful full table load.  If a partial table
           load is desired then this logic would have to change. */
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to load Config Table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitConfigTbl_Exit_Tag;
    }

    /* Load Config table file */
    iStatus = CFE_TBL_Load(MixerConfigTblHdl,
                           CFE_TBL_SRC_FILE,
                           PMC_MIXER_CONFIG_TABLE_FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, CFE_SUCCESS is for a successful full table load.  If a partial table
           load is desired then this logic would have to change. */
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to load Config Table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_InitConfigTbl_Exit_Tag;
    }

    iStatus = AcquireConfigPointers();

PMC_InitConfigTbl_Exit_Tag:
    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Validate Config Table                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 PMC::ValidatePwmCfgTbl(void* ConfigTblPtr)
{
    int32  iStatus=0;
    PMC_PwmConfigTbl_t* PMC_PwmConfigTblPtr = (PMC_PwmConfigTbl_t*)(ConfigTblPtr);

    if (ConfigTblPtr == NULL)
    {
        iStatus = -1;
        goto PMC_ValidatePwmCfgTbl_Exit_Tag;
    }

    /* TODO:  Add code to validate new data values here.
    **
    ** Examples:
    ** if (PMC_ConfigTblPtr->iParam <= 16) {
    **   (void) CFE_EVS_SendEvent(PMC_CONFIG_TABLE_INF_EID, CFE_EVS_ERROR,
     *                         "Invalid value for Config parameter sParam (%d)",
    **                         PMC_ConfigTblPtr->iParam);
    ** }
    **/

PMC_ValidatePwmCfgTbl_Exit_Tag:
    return (iStatus);
}

int32 PMC::ValidateMixerCfgTbl(void* ConfigTblPtr)
{
    int32  iStatus=0;
    MultirotorMixer_ConfigTable_t* TblPtr = (MultirotorMixer_ConfigTable_t*)(ConfigTblPtr);

    if (ConfigTblPtr == NULL)
    {
        iStatus = -1;
        goto PMC_ValidateMixerCfgTbl_Exit_Tag;
    }

    /* TODO:  Add code to validate new data values here.
    **
    ** Examples:
    ** if (PMC_ConfigTblPtr->iParam <= 16) {
    **   (void) CFE_EVS_SendEvent(PMC_CONFIG_TABLE_INF_EID, CFE_EVS_ERROR,
     *                         "Invalid value for Config parameter sParam (%d)",
    **                         PMC_ConfigTblPtr->iParam);
    ** }
    **/

PMC_ValidateMixerCfgTbl_Exit_Tag:
    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process New Config Table                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void PMC::ProcessNewPwmConfigTbl()
{
    /* TODO:  Add code to set new Config parameters with new values here.
    **
    ** Examples:
    **
    **    latest_sParam = ConfigTblPtr->sParam;
    **    latest_fParam = PMC.AppData.ConfigTblPtr->fParam;
    */
}

void PMC::ProcessNewMixerConfigTbl()
{
    /* TODO:  Add code to set new Config parameters with new values here.
    **
    ** Examples:
    **
    **    latest_sParam = ConfigTblPtr->sParam;
    **    latest_fParam = PMC.AppData.ConfigTblPtr->fParam;
    */
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Acquire Config Pointers                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 PMC::AcquireConfigPointers(void)
{
    int32 iStatus = CFE_SUCCESS;

    /*
    ** Release the table
    */
    /* TODO: This return value can indicate success, error, or that the info has been 
     * updated.  We ignore this return value in favor of checking CFE_TBL_Manage(), but
     * be sure this is the behavior you want. */
    (void) CFE_TBL_ReleaseAddress(PwmConfigTblHdl);

    /*
    ** Manage the table
    */
    iStatus = CFE_TBL_Manage(PwmConfigTblHdl);
    if ((iStatus != CFE_SUCCESS) && (iStatus != CFE_TBL_INFO_UPDATED))
    {
        (void) CFE_EVS_SendEvent(PMC_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to manage PWM Config table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_AcquireConfigPointers_Exit_Tag;
    }

    iStatus = CFE_TBL_Manage(MixerConfigTblHdl);
    if ((iStatus != CFE_SUCCESS) && (iStatus != CFE_TBL_INFO_UPDATED))
    {
        (void) CFE_EVS_SendEvent(PMC_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to manage Mixer Config table (0x%08X)",
                                 (unsigned int)iStatus);
        goto PMC_AcquireConfigPointers_Exit_Tag;
    }

    /*
    ** Get a pointer to the table
    */
    iStatus = CFE_TBL_GetAddress((void**)&PwmConfigTblPtr,
                                 PwmConfigTblHdl);
    if (iStatus == CFE_TBL_INFO_UPDATED)
    {
        ProcessNewPwmConfigTbl();
        iStatus = CFE_SUCCESS;
    }
    else if(iStatus != CFE_SUCCESS)
    {
    	PwmConfigTblPtr = 0;
        (void) CFE_EVS_SendEvent(PMC_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to get PWM Config table's address (0x%08X)",
                                 (unsigned int)iStatus);
    }

    iStatus = CFE_TBL_GetAddress((void**)&MixerConfigTblPtr,
                                 MixerConfigTblHdl);
    if (iStatus == CFE_TBL_INFO_UPDATED)
    {
        ProcessNewMixerConfigTbl();
        iStatus = CFE_SUCCESS;
    }
    else if(iStatus != CFE_SUCCESS)
    {
    	MixerConfigTblPtr = 0;
        (void) CFE_EVS_SendEvent(PMC_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to get Mixer Config table's address (0x%08X)",
                                 (unsigned int)iStatus);
    }

PMC_AcquireConfigPointers_Exit_Tag:
    return (iStatus);

} /* End of PMC_AcquirePointers */


#ifdef __cplusplus
}
#endif

/************************/
/*  End of File Comment */
/************************/
    
