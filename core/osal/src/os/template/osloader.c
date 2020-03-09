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

#include "osapi.h"
#include <string.h>



int32 OS_ModuleTableInit( void )
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_SymbolLookup(cpuaddr *symbol_address, const char *symbol_name )
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_SymbolTableDump( const char *filename, uint32 size_limit )
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_ModuleLoad( uint32 *module_id, const char *module_name, const char *filename )
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_ModuleUnload( uint32 module_id )
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_ModuleInfo( uint32 module_id, OS_module_prop_t *module_info )
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}


