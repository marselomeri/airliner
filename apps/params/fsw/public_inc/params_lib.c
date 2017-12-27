
/************************************************************************
** Includes
*************************************************************************/
#include "params_lib.h"


// TODO: Check with Matt that this isn't awful
PARAMS_ParamData_t* PARAMS_GetParam(void* tblPtr, uint32 tblSize, char* name)
{
	PARAMS_ParamData_t* retData = 0;

	/* Iterate over passed table to find param with passed name */
	for(int i = 0; i < tblSize; ++i)
	{
//		if (strcmp(tblPtr->param_data[i].name, name) == 0)
//		{
//			retData = tblPtr->param_data[i];
//		}
	}

	return retData;
}



/************************/
/*  End of File Comment */
/************************/
