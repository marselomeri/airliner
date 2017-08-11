
/************************************************************************
** Pragmas
*/

/*
** Include Files
*/
#include "app.h"
#include "tbl.h"
#include "cfe_tbl_filedef.h"
#include "to_platform_cfg.h"
#include "to_mission_cfg.h"
#include "msg_ids.h"

/*
** Local Defines
*/


/*
** Local Structure Declarations
*/

CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    "to_ConfigTable", "TO.to_config", "TO config table",
    "to_config.tbl", sizeof(TO_Table_t)
};

/*
** Default TO iLoad table data
*/

/************************************************************************
** Global Variables
*************************************************************************/

#define TO_PQUEUE_GROUND_SINGLE_PASS_IDX		0
#define TO_PQUEUE_GROUND_HIGH_OPS_RSRVD_IDX		1
#define TO_PQUEUE_GROUND_HIGH_IDX				2
#define TO_PQUEUE_GROUND_MEDIUM_IDX				3
#define TO_PQUEUE_GROUND_LOW_IDX				4
#define TO_PQUEUE_ONBOARD_SINGLE_PASS_IDX		5
#define TO_PQUEUE_ONBOARD_HIGH_OPS_RSRVD_IDX	6
#define TO_PQUEUE_ONBOARD_HIGH_IDX				7
#define TO_PQUEUE_ONBOARD_MEDIUM_IDX			8
#define TO_PQUEUE_ONBOARD_LOW_IDX				9

#define TO_CHANNEL_GROUND						0
#define TO_CHANNEL_ONBOARD						1

TO_Table_t to_ConfigTable =
{
	/* Table ID */
	1,
	{
		{ TO_QUEUE_ENABLED,  50,  10000,     TO_CHANNEL_PILOT, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,  50,    500000,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,  200,    250000,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED, 100,     20000,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED, 100,     20000,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED, 100,     20000,       TO_CHANNEL_CFDP, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},

		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},

		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_TLM,	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,   1, 1, TO_CHANNEL_PX4,	0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},

		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0}
	},
	{
		{TO_CHANNEL_ENABLED, "127.0.0.1", 14550, 0 },
		{TO_CHANNEL_ENABLED, "127.0.0.1",  5011, 0 },
		{TO_CHANNEL_ENABLED, "127.0.0.1",  5011, 0 },
		{TO_CHANNEL_ENABLED, "127.0.0.1",  5011, 0 }
	}
};



/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/

#ifdef	__cplusplus
}
#endif

#endif /* _TO_CONFIG_ */
