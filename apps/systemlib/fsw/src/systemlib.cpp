/*************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "systemlib_version.h"
#include "mixer.h"

extern "C" {

/*************************************************************************
** Macro Definitions
*************************************************************************/


/*************************************************************************
** Private Function Prototypes
*************************************************************************/
int32 SYSTEMLIB_LibInit(void);
int32 SYSTEMLIB_MixerCallback(cpuaddr Handle,
                        uint8 ControlGroup,
                        uint8 ControlIndex,
                        float &Control);


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* CFS Library Initialization Routine                              */
/* cFE requires that a library have an initialization routine      */ 
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 SYSTEMLIB_LibInit(void)
{
    MultirotorGeometry geometry;

    MultirotorMixer mixer(SYSTEMLIB_MixerCallback,
            0, geometry, 0.0, 0.0, 0.0, 0.0);

    OS_printf ("SystemLib Initialized.  Version %d.%d.%d.%d\n",
            SYSTEMLIB_MAJOR_VERSION,
            SYSTEMLIB_MINOR_VERSION,
            SYSTEMLIB_REVISION,
            SYSTEMLIB_MISSION_REV);
                
    return CFE_SUCCESS;
 
}/* End SYSTEMLIB_LibInit */


int32  SYSTEMLIB_MixerCallback(cpuaddr Handle,
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
