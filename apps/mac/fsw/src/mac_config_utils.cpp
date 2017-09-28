/****************************************************************************
 *
 *   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "mac_app.h"

/************************************************************************
** Function Definitions
*************************************************************************/


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Config Table                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MAC::InitConfigTbl()
{
    int32  iStatus=0;

    /* Register Config table */
    iStatus = CFE_TBL_Register(&PwmConfigTblHdl,
                               MAC_PWM_CONFIG_TABLENAME,
                               (sizeof(MAC_PwmConfigTbl_t)),
                               CFE_TBL_OPT_DEFAULT,
							   MAC::ValidatePwmCfgTbl);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, a critical table could return another nominal code.  If this table is
         * made critical this logic would have to change. */
        (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to register PWM table (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_InitConfigTbl_Exit_Tag;
    }

    /* Register Mixer table */
    iStatus = CFE_TBL_Register(&MixerConfigTblHdl,
                               MAC_MIXER_CONFIG_TABLENAME,
                               (sizeof(MultirotorMixer_ConfigTable_t)),
                               CFE_TBL_OPT_DEFAULT,
							   MAC::ValidateMixerCfgTbl);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, a critical table could return another nominal code.  If this table is
         * made critical this logic would have to change. */
        (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to register Mixer table (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_InitConfigTbl_Exit_Tag;
    }

    /* Load Config table file */
    iStatus = CFE_TBL_Load(PwmConfigTblHdl,
                           CFE_TBL_SRC_FILE,
                           MAC_PWM_CONFIG_TABLE_FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, CFE_SUCCESS is for a successful full table load.  If a partial table
           load is desired then this logic would have to change. */
        (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to load Config Table (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_InitConfigTbl_Exit_Tag;
    }

    /* Load Config table file */
    iStatus = CFE_TBL_Load(MixerConfigTblHdl,
                           CFE_TBL_SRC_FILE,
                           MAC_MIXER_CONFIG_TABLE_FILENAME);
    if (iStatus != CFE_SUCCESS)
    {
        /* Note, CFE_SUCCESS is for a successful full table load.  If a partial table
           load is desired then this logic would have to change. */
        (void) CFE_EVS_SendEvent(MAC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to load Config Table (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_InitConfigTbl_Exit_Tag;
    }

    iStatus = AcquireConfigPointers();

MAC_InitConfigTbl_Exit_Tag:
    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Validate PWM Configuration Table                                */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MAC::ValidatePwmCfgTbl(void* ConfigTblPtr)
{
    int32  iStatus=0;
    MAC_PwmConfigTbl_t* MAC_PwmConfigTblPtr = (MAC_PwmConfigTbl_t*)(ConfigTblPtr);

    if (ConfigTblPtr == NULL)
    {
        iStatus = -1;
        goto MAC_ValidatePwmCfgTbl_Exit_Tag;
    }

    /* TODO:  Add code to validate new data values here.
    **
    ** Examples:
    ** if (MAC_ConfigTblPtr->iParam <= 16) {
    **   (void) CFE_EVS_SendEvent(MAC_CONFIG_TABLE_INF_EID, CFE_EVS_ERROR,
     *                         "Invalid value for Config parameter sParam (%d)",
    **                         MAC_ConfigTblPtr->iParam);
    ** }
    **/

MAC_ValidatePwmCfgTbl_Exit_Tag:
    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Validate Mixer Configuration Table                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MAC::ValidateMixerCfgTbl(void* ConfigTblPtr)
{
    int32  iStatus=0;
    MultirotorMixer_ConfigTable_t* TblPtr = (MultirotorMixer_ConfigTable_t*)(ConfigTblPtr);

    if (ConfigTblPtr == NULL)
    {
        iStatus = -1;
        goto MAC_ValidateMixerCfgTbl_Exit_Tag;
    }

    /* TODO:  Add code to validate new data values here.
    **
    ** Examples:
    ** if (MAC_ConfigTblPtr->iParam <= 16) {
    **   (void) CFE_EVS_SendEvent(MAC_CONFIG_TABLE_INF_EID, CFE_EVS_ERROR,
     *                         "Invalid value for Config parameter sParam (%d)",
    **                         MAC_ConfigTblPtr->iParam);
    ** }
    **/

MAC_ValidateMixerCfgTbl_Exit_Tag:
    return (iStatus);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Acquire Config Pointers                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MAC::AcquireConfigPointers(void)
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
        (void) CFE_EVS_SendEvent(MAC_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to manage PWM Config table (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_AcquireConfigPointers_Exit_Tag;
    }

    iStatus = CFE_TBL_Manage(MixerConfigTblHdl);
    if ((iStatus != CFE_SUCCESS) && (iStatus != CFE_TBL_INFO_UPDATED))
    {
        (void) CFE_EVS_SendEvent(MAC_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to manage Mixer Config table (0x%08X)",
                                 (unsigned int)iStatus);
        goto MAC_AcquireConfigPointers_Exit_Tag;
    }

    /*
    ** Get a pointer to the table
    */
    iStatus = CFE_TBL_GetAddress((void**)&PwmConfigTblPtr,
                                 PwmConfigTblHdl);
    if (iStatus == CFE_TBL_INFO_UPDATED)
    {
        iStatus = CFE_SUCCESS;
    }
    else if(iStatus != CFE_SUCCESS)
    {
    	PwmConfigTblPtr = 0;
        (void) CFE_EVS_SendEvent(MAC_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to get PWM Config table's address (0x%08X)",
                                 (unsigned int)iStatus);
    }

    iStatus = CFE_TBL_GetAddress((void**)&MixerConfigTblPtr,
                                 MixerConfigTblHdl);
    if (iStatus == CFE_TBL_INFO_UPDATED)
    {
        iStatus = CFE_SUCCESS;
    }
    else if(iStatus != CFE_SUCCESS)
    {
    	MixerConfigTblPtr = 0;
        (void) CFE_EVS_SendEvent(MAC_CONFIG_TABLE_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to get Mixer Config table's address (0x%08X)",
                                 (unsigned int)iStatus);
    }

MAC_AcquireConfigPointers_Exit_Tag:
    return (iStatus);

}


#ifdef __cplusplus
}
#endif

/************************/
/*  End of File Comment */
/************************/
    
