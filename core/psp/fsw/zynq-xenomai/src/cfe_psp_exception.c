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
**  Include Files
*/
#include <stdio.h>
#include <string.h>

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"
#include "cfe_es.h"            /* For reset types */
#include "cfe_platform_cfg.h"  /* for processor ID */
#include "cfe_psp.h"

/*
** Types and prototypes for this module
*/

/*
** PSP Specific defines
*/

/*
**  External Declarations
*/

/*
** Global variables
*/

CFE_PSP_ExceptionContext_t CFE_PSP_ExceptionContext;
char                       CFE_PSP_ExceptionReasonString[256];

/*
**
** Imported Functions
**
*/

void CFE_ES_ProcessCoreException(uint32  HostTaskId,  const char *ReasonString,
                                 const uint32 *ContextPointer, uint32 ContextSize);

/*
**
** Local Function Prototypes
**
*/

void CFE_PSP_ExceptionHook ( int task_id, int vector, uint8 *pEsf );


/***************************************************************************
 **                        FUNCTION DEFINITIONS
 ***************************************************************************/

/*
**
**   Name: CFE_PSP_AttachExceptions
**
**   Purpose: This function Initializes the task execptions and adds a hook
**              into the system exception handling.
**
*/

void CFE_PSP_AttachExceptions(void)
{
   OS_printf("CFE_PSP: CFE_PSP_AttachExceptions Called\n");

}


/*
** Name: CFE_PSP_ExceptionHook
**
** Purpose: Make the proper call to CFE_ES_EXCEPTION_FUNCTION (defined in
**          cfe_es_platform.cfg)
**
*/
void CFE_PSP_ExceptionHook (int task_id, int vector, uint8 *pEsf )
{

    sprintf(CFE_PSP_ExceptionReasonString, "Processor Exception %d, task ID %d", vector, task_id);

    /*
    ** Save Exception Stack frame
    */
    memcpy(&(CFE_PSP_ExceptionContext.regs), pEsf, (32*4));

    /*
    ** Call the Generic cFE routine to finish processing the exception and
    ** restart the cFE
    */
    CFE_ES_ProcessCoreException((uint32)task_id, (uint8 *)CFE_PSP_ExceptionReasonString,
                                (uint32 *)&CFE_PSP_ExceptionContext, sizeof(CFE_PSP_ExceptionContext_t));

    /*
    ** No return to here
    */

} /* end function */


/*
**
**   Name: CFE_PSP_SetDefaultExceptionEnvironment
**
**   Purpose: This function sets a default exception environment that can be used
**
**   Notes: The exception environment is local to each task Therefore this must be
**          called for each task that that wants to do floating point and catch exceptions
**          Currently, this is automaticall called from OS_TaskRegister for every task
*/

void CFE_PSP_SetDefaultExceptionEnvironment(void)
{
   return;
}
