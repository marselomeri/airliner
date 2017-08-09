
#include "uttest.h"

#include "vc_app_test.h"
//#include "vc_cmds_test.h"
//#include "vc_config_tbl_test.h"
//#include "vc_cds_tbl_test.h"

int main(void)
{   
    VC_App_Test_AddTestCases();
    //VC_Cmds_Test_AddTestCases();
    //VC_Config_Tbl_Test_AddTestCases();
    //VC_CDS_Tbl_Test_AddTestCases();

    return(UtTest_Run());

}

