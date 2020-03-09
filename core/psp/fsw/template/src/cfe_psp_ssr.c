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
#include "cfe_psp_config.h"

/*
**  Standard Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/******************************************************************************
**  Function:  CFE_PSP_InitSSR
**
**  Purpose:
**    Initializes the Solid State Recorder device. This can be filled in for the platform.
**
**  Arguments:
**    bus, device, device name
**
**  Return:
**    (none)
*/

int32 CFE_PSP_InitSSR(uint32 bus, uint32 device, char *DeviceName )
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}

