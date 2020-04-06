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

/****************************************************************************************
                                    INCLUDE FILES
****************************************************************************************/

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

#include "common_types.h"
#include "osapi.h"


/****************************************************************************************
                                     DEFINES
****************************************************************************************/



/****************************************************************************************
                                   GLOBAL DATA
****************************************************************************************/


/****************************************************************************************
                                INITIALIZATION FUNCTION
****************************************************************************************/


/****************************************************************************************
                                    Network API
****************************************************************************************/
/*--------------------------------------------------------------------------------------
    Name: OS_NetworkGetID
    
    Purpose: Gets the ID of the current Network 

    Returns: OS_ERROR if the  host id could not be found
             a 32 bit host id if success
---------------------------------------------------------------------------------------*/
int32 OS_NetworkGetID             (void)
{
   long    host_id = 0;

   host_id = gethostid();

   return (host_id);
    
}/* end OS_NetworkGetID */
/*--------------------------------------------------------------------------------------
    Name: OS_NetworkGetHostName
    
    Purpose: Gets the name of the current host

    Returns: OS_ERROR if the  host name could not be found
             OS_SUCCESS if the name was copied to host_name successfully
---------------------------------------------------------------------------------------*/

int32 OS_NetworkGetHostName       (char *host_name, uint32 name_len)
{
   int    retval;
   uint32 return_code;
   
   if ( host_name == NULL)
   {
      return_code = OS_INVALID_POINTER;
   }
   else if ( name_len == 0 )
   {
      return_code = OS_ERROR;
   }
   else
   {
      retval = gethostname( host_name, name_len);
      if ( retval == -1 )
      {
      
         return_code = OS_ERROR;
      }
      else
      {
         return_code = OS_SUCCESS;
      }
   }

   return(return_code);
}/* end OS_NetworkGetHostName */



