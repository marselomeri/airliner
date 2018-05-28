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

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/

#define TO_PQUEUE_SINGLE_PASS_IDX		0
#define TO_PQUEUE_HIGH_OPS_RSRVD_IDX	        1
#define TO_PQUEUE_HIGH_IDX			2
#define TO_PQUEUE_MEDIUM_IDX			3
#define TO_PQUEUE_LOW_IDX			4

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
		{CFE_ES_HK_TLM_MID,		        1,	  TO_PQUEUE_MEDIUM_IDX},
		{SENS_HK_TLM_MID,			1,	  TO_PQUEUE_MEDIUM_IDX},
		{GPS_HK_TLM_MID,			1,	  TO_PQUEUE_MEDIUM_IDX},
        {PX4_VEHICLE_GLOBAL_POSITION_MID,       1,        TO_PQUEUE_MEDIUM_IDX},
        {PX4_POSITION_SETPOINT_TRIPLET_MID,       1,        TO_PQUEUE_MEDIUM_IDX}
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

CFE_TBL_FILEDEF(TO_ConfigTbl, TO.GRND_PB_CFG, TO ground config table, to_grnd_pb.tbl )

/************************/
/*  End of File Comment */
/************************/
