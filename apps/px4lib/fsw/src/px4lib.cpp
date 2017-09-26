/*************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "px4lib_version.h"
#include "MultirotorMixer.h"

extern "C" {

/*************************************************************************
** Macro Definitions
*************************************************************************/


/*************************************************************************
** Private Function Prototypes
*************************************************************************/
int32 PX4LIB_LibInit(void);
int32 PX4LIB_MixerCallback(cpuaddr Handle,
                        uint8 ControlGroup,
                        uint8 ControlIndex,
                        float &Control);


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CFS Library Initialization Routine                              */
/* cFE requires that a library have an initialization routine      */ 
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 PX4LIB_LibInit(void)
{
    OS_printf ("PX4 Library Initialized.  Version %d.%d.%d.%d\n",
    		PX4LIB_MAJOR_VERSION,
			PX4LIB_MINOR_VERSION,
			PX4LIB_REVISION,
			PX4LIB_MISSION_REV);
                
    return CFE_SUCCESS;
 
}/* End PX4LIB_LibInit */


int32 PX4LIB_MixerCallback(cpuaddr Handle,
                        uint8 ControlGroup,
                        uint8 ControlIndex,
                        float &Control)
{
    Control = 0.0;
    return 0;
}

}

/************************/
/*  End of File Comment */
/************************/
