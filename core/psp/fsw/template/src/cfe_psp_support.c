/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"
#include "cfe_es.h"            /* For reset types */
#include "cfe_platform_cfg.h"  /* for processor ID */
#include "cfe_mission_cfg.h"   /* for spacecraft ID */

/*
** Types and prototypes for this module
*/
#include "cfe_psp.h"
#include "cfe_psp_private.h"



/******************************************************************************
**  Function:  CFE_PSP_Restart()
**
**  Purpose:
**    Provides a common interface to the processor reset.
**
**  Arguments:
**    reset_type  : Type of reset.
**
**  Return:
**    (none)
*/

void CFE_PSP_Restart(uint32 reset_type)
{
    OS_printf("%s\n", __FUNCTION__);
}

/******************************************************************************
**  Function:  CFE_PSP_Panic()
**
**  Purpose:
**    Provides a common interface to abort the cFE startup process and return
**    back to the OS.
**
**  Arguments:
**    ErrorCode  : Reason for Exiting.
**
**  Return:
**    (none)
*/

void CFE_PSP_Panic(int32 ErrorCode)
{
    OS_printf("%s\n", __FUNCTION__);
}


/******************************************************************************
**  Function:  CFE_PSP_FlushCaches)
**
**  Purpose:
**    Provides a common interface to flush the processor caches. This routine
**    is in the BSP because it is sometimes implemented in hardware and
**    sometimes taken care of by the RTOS.
**
**  Arguments:
**
**  Return:
**    (none)
*/
void CFE_PSP_FlushCaches(uint32 type, cpuaddr address, uint32 size)
{
    OS_printf("%s\n", __FUNCTION__);
}

/*
** Name: CFE_PSP_GetProcessorId
**
** Purpose:
**         return the processor ID.
**
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
**
** Return Values: Processor ID
*/
uint32 CFE_PSP_GetProcessorId    (void)
{
    OS_printf("%s\n", __FUNCTION__);

    return 0;
}


/*
** Name: CFE_PSP_GetSpacecraftId
**
** Purpose:
**         return the spacecraft ID.
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: Spacecraft ID
*/
uint32 CFE_PSP_GetSpacecraftId   (void)
{
    OS_printf("%s\n", __FUNCTION__);

    return 0;
}
