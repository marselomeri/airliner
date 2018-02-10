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
    "TO_ConfigTbl", "TO.GRND_PB_CFG", "TO ground config table",
    "to_grnd_pb.tbl", (sizeof(TO_ChannelTbl_t))
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
	TO_OUTPUT_TYPE_PROTOBUF,
	{
		/* Message Flows */
		/* Ground Queues */
		{CFE_ES_HK_TLM_MID,			1,	TO_PQUEUE_MEDIUM_IDX}
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
		{TO_PQUEUE_ENA, 100, TO_PRIORITY_QUEUE_TYPE_FIFO}
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
