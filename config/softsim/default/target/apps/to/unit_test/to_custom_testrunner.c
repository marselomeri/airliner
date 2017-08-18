#include "uttest.h"

#include "to_app_custom_test.h"

TO_AppData_t TO_AppData;

extern int enable_wrappers;

int main(void)
{   
    int testResults = 0;
    enable_wrappers = 1;
    VC_Custom_App_Test_AddTestCases();
    testResults =  UtTest_Run();

    enable_wrappers = 0;

    return testResults;
}
