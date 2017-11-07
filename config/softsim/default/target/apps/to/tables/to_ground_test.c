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
* 3. Neither the name Windhover Labs nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
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
*****************************************************************************/

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe_tbl_filedef.h"
#include "to_tbldefs.h"
#include "msg_ids.h"

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Definitions
*************************************************************************/

/**
** \brief The cFE TO config table definition.
**
** Content format: ObjName[64], TblName[38], Desc[32], TgtFileName[20], ObjSize
**    ObjName - variable name of config table, e.g., TO_ConfigDefTbl[]
**    TblName - app's table name, e.g., TO.CONFIG_TBL, where TO is the same app name
**              used in cfe_es_startup.scr, and TO_defConfigTbl is the same table
**              name passed in to CFE_TBL_Register()
**    Desc - description of table in string format
**    TgtFileName[20] - table file name, compiled as .tbl file extension
**    ObjSize - size of the entire table
**
*/
static CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    "TO_ConfigTbl", "TO.GROUND_CFG", "TO ground config table",
    "to_ground_test.tbl", (sizeof(TO_ChannelTbl_t))
};

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/

#define TO_PQUEUE_SINGLE_PASS_IDX		0
#define TO_PQUEUE_HIGH_OPS_RSRVD_IDX	1
#define TO_PQUEUE_HIGH_IDX				2
#define TO_PQUEUE_MEDIUM_IDX			3
#define TO_PQUEUE_LOW_IDX				4

/**
**  \brief Default TO config table data
*/
TO_ChannelTbl_t TO_ConfigTbl =
{
	/* Table ID */
	1,
	{
		/* Message Flows */
		/* Ground Queues */
		{CFE_EVS_HK_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{CFE_SB_HK_TLM_MID,			1,	TO_PQUEUE_MEDIUM_IDX},
		{CFE_TBL_HK_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{CFE_TIME_HK_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{CFE_TIME_DIAG_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{CFE_EVS_EVENT_MSG_MID,		32, TO_PQUEUE_MEDIUM_IDX},
		{CFE_SB_STATS_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{CFE_ES_APP_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{CFE_TBL_REG_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{CFE_SB_ONESUB_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{CFE_ES_SHELL_TLM_MID,		32, TO_PQUEUE_MEDIUM_IDX},
		{CFE_ES_MEMSTATS_TLM_MID,	1,	TO_PQUEUE_MEDIUM_IDX},
		{CF_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{CF_TRANS_TLM_MID,			1,	TO_PQUEUE_MEDIUM_IDX},
		{CF_CONFIG_TLM_MID,			1,	TO_PQUEUE_MEDIUM_IDX},
		{CF_SPACE_TO_GND_PDU_MID,	32,	TO_PQUEUE_MEDIUM_IDX},
		{CS_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{DS_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{DS_DIAG_TLM_MID,			1,	TO_PQUEUE_MEDIUM_IDX},
		{FM_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{FM_FILE_INFO_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{FM_DIR_LIST_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{FM_OPEN_FILES_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{FM_FREE_SPACE_TLM_MID,		1,	TO_PQUEUE_MEDIUM_IDX},
		{HK_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{HS_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{LC_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{MD_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{MM_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{SCH_HK_TLM_MID,			1,	TO_PQUEUE_MEDIUM_IDX},
		{SCH_DIAG_TLM_MID,			1,	TO_PQUEUE_MEDIUM_IDX},
		{CI_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{TO_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
		{TO_DATA_TYPE_MID,			1,	TO_PQUEUE_MEDIUM_IDX},
		{EA_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX},
        {VC_HK_TLM_MID,				1,	TO_PQUEUE_MEDIUM_IDX}
	},{
		/* Priority Queues */
		/* TO_PQUEUE_SINGLE_PASS_IDX */
		{TO_PQUEUE_ENA, 100, TO_PRIORITY_QUEUE_TYPE_SINGLE},
		/* TO_PQUEUE_HIGH_OPS_RSRVD_IDX */
		{TO_PQUEUE_ENA, 100, TO_PRIORITY_QUEUE_TYPE_FIFO},
		/* TO_PQUEUE_HIGH_IDX */
		{TO_PQUEUE_ENA, 100, TO_PRIORITY_QUEUE_TYPE_FIFO},
		/* TO_PQUEUE_MEDIUM_IDX */
		{TO_PQUEUE_ENA, 100, TO_PRIORITY_QUEUE_TYPE_FIFO},
		/* TO_PQUEUE_LOW_IDX */
		{TO_PQUEUE_ENA, 100, TO_PRIORITY_QUEUE_TYPE_FIFO},
	}
};

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Prototypes
*************************************************************************/

/************************************************************************
** Function Definitions
*************************************************************************/

/************************/
/*  End of File Comment */
/************************/
