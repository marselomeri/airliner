/******************************************************************************
** File:  bsp_start.c
**
**
**      This is governed by the NASA Open Source Agreement and may be used, 
**      distributed and modified only pursuant to the terms of that agreement. 
**
**      Copyright (c) 2004-2006, United States government as represented by the 
**      administrator of the National Aeronautics Space Administration.  
**      All rights reserved. 
**
**
** Purpose:
**   OSAL BSP main entry point.
**
** History:
**   2005/07/26  A. Cudmore      | Initial version for linux 
**
******************************************************************************/

/*
** OSAL includes 
*/
#include "osapi.h"

/*
** Types and prototypes for this module
*/

/*
**  External Declarations
*/
void OS_Application_Startup(void);
                                                                           
/*
** Global variables
*/


                                                                                                                                                
/******************************************************************************
**  Function:  main()
**
**  Purpose:
**    BSP Application entry point.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/

int main(int argc, char *argv[])
{
   /*
   ** OS_API_Init is called by OS_Application_Startup
   ** Also note that OS_API_Init now also takes care of signal masking
   */

   /*
   ** Call application specific entry point.
   */
   OS_Application_Startup();

   /*
   ** OS_IdleLoop() will wait forever and return if
   ** someone calls OS_ApplicationShutdown(TRUE)
   */
   OS_IdleLoop();

   /* Should typically never get here */
   return(EXIT_SUCCESS);
}



/* undefined symbols ----------------------------------------------------------
 * added prototypes here so that the code compiles and runs w/o error
 * if there is still code that calls these functions, we will get a message
 *
 * ld<cfe-core.o
Warning: module 0x461d010 holds reference to undefined symbol vxFpscrGet.
Warning: module 0x461d010 holds reference to undefined symbol vxFpscrSet.

These do not seem to be included in 85xx build, but are

"defined(_PPC_) && CPU != PPC440" in vxworks osapi.c, line 2707

STUB them for now to build.  These are FPU exception handler functions that
are currently not used
 * *******/

unsigned int bsp_ut_FPMask = 0;

unsigned int vxFpscrGet(void)
{
    printf("%s->%s<stub>:%d:\n", __FILE__, __func__, __LINE__);

    return(bsp_ut_FPMask);
}

void vxFpscrSet(unsigned int x)
{
    printf("%s->%s<stub>:%d:\n", __FILE__, __func__, __LINE__);

    bsp_ut_FPMask = x;
}


