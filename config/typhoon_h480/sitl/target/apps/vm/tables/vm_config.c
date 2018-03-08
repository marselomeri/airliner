/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe_tbl_filedef.h"
#include "vm_tbldefs.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/
static OS_USED CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    /* Content format: ObjName[64], TblName[38], Desc[32], TgtFileName[20], ObjSize
    **    ObjName - variable name of config table, e.g., CI_ConfigDefTbl[]
    **    TblName - app's table name, e.g., CI.CONFIG_TBL, where CI is the same app name
    **              used in cfe_es_startup.scr, and CI_defConfigTbl is the same table
    **              name passed in to CFE_TBL_Register()
    **    Desc - description of table in string format
    **    TgtFileName[20] - table file name, compiled as .tbl file extension
    **    ObjSize - size of the entire table
    */

    "VM_ConfigTbl", "VM.CONFIG_TBL", "VM default config table",
    "vm_config.tbl", (sizeof(VM_ConfigTbl_t))
};

/*
** External Global Variables
*/

/*
** Global Variables
*/

/* Default ULR config table data */
VM_ConfigTbl_t VM_ConfigTbl =
{
		//SYS_AUTOSTART (for hil)
		6001,
		//COM_RC_IN_MODE
		2,
		//COM_ARM_SWISBTN
		0,
		//COM_ARM_WO_GPS
		1,
		//COM_ARM_MIS_REQ
		0,
		//COM_RC_ARM_HYST
		1000,
		//MAV_TYPE
		13,
		//MAV_SYS_ID
		1,
		//MAV_COMP_ID
		1,
		//CBRK_SUPPLY_CHK
		0,
		//CBRK_USB_CHK
		0,
		//CBRK_AIRSPD_CHK
		0,
		//CBRK_ENGINEFAIL
		284953,
		//CBRK_GPSFAIL
		0,
		//CBRK_FLIGHTTERM
		121212,
		//CBRK_VELPOSERR
		0,
		//	NAV_DLL_ACT
		2,
		//	NAV_RCL_ACT
		2,
		//	COM_DL_LOSS_T
		10,
		//	COM_RC_LOSS_T
		0.5,
		//	COM_RC_STICK_OV
		12.0,
		//	COM_RC_OVERRIDE
		0,
		//	COM_DL_REG_T
		0,
		//	COM_EF_THROT
		0.5,
		//	COM_EF_C2T
		0.5,
		//	COM_EF_TIME
		10.0,
		//	GF_ACTION
		1,
		//	COM_DISARM_LAND
		3,
		//	COM_LOW_BAT_ACT
		1,
		//	COM_OF_LOSS_T
		0.0,
		//	COM_OBL_ACT
		0,
		//	COM_OBL_RC_ACT
		0,
		//	COM_HOME_H_T
		5.0,
		//	COM_HOME_V_T
		10.0,
		//	COM_FLTMODE1
		-1,
		//	COM_FLTMODE2
		-1,
		//	COM_FLTMODE3
		-1,
		//	COM_FLTMODE4
		-1,
		//	COM_FLTMODE5
		-1,
		//	COM_FLTMODE6
		-1,
		//	COM_ARM_EKF_POS
		0.5,
		//	COM_ARM_EKF_VEL
		0.5,
		//	COM_ARM_EKF_HGT
		1.0,
		//	COM_ARM_EKF_YAW
		0.5,
		//	COM_ARM_EKF_AB
		0.0050,
		//	COM_ARM_EKF_GB
		0.0009,
		//	COM_ARM_IMU_ACC
		0.7,
		//	COM_ARM_IMU_GYR
		0.2,
		//	COM_POSCTL_NAVL
		0


};

/*
** Local Variables
*/

/*
** Function Prototypes
*/

/*
** Function Definitions
*/

/*=======================================================================================
** End of file vm_config.c
**=====================================================================================*/
    
