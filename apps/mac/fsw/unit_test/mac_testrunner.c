#include "uttest.h"

#include "mac_app_test.h"
#include "mac_cmds_test.h"
#include "mac_config_tbl_test.h"
#include "mac_cds_tbl_test.h"

int main(void)
{   
    MAC_App_Test_AddTestCases();
    MAC_Cmds_Test_AddTestCases();
    MAC_Config_Tbl_Test_AddTestCases();
    MAC_CDS_Tbl_Test_AddTestCases();

    return(UtTest_Run());

}

