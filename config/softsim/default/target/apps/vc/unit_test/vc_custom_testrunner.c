#include "uttest.h"

#include "vc_app_custom_device_test.h"
#include "vc_app_custom_transmit_test.h"
#include "vc_app.h"
//#include "vc_cmds_test.h"
//#include "vc_config_tbl_test.h"
//#include "vc_cds_tbl_test.h"

VC_AppData_t VC_AppData;

extern int enable_wrappers;

int main(void)
{   
	int testResults = 0;
	enable_wrappers = 1;
    VC_Custom_App_Device_Test_AddTestCases();
    VC_Custom_App_Transmit_Test_AddTestCases();
    //VC_Cmds_Test_AddTestCases();
    //VC_Config_Tbl_Test_AddTestCases();
    //VC_CDS_Tbl_Test_AddTestCases();
    testResults =  UtTest_Run();

    enable_wrappers = 0;

    return testResults;
}
