/* Airliner includes. */
#include "cfe_psp_private.h"
#include "cfe_platform_cfg.h"
#include <FreeRTOS.h>


/* Forward declaration to decouple PSP from the CFE package. */
void CFE_ES_Main(unsigned long int StartType, unsigned long int StartSubtype, unsigned long int ModeId, const char *StartFilePath );



int main( void )
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}
