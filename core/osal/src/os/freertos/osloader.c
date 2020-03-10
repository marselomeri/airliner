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

#include <nuttx/symtab.h>
#include "osapi.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include <string.h>


#define OS_DL_SYMTBL_MAX_LINE_LENGTH   (512)

symtab_s OS_DL_Exports[OS_DL_EXPORT_MAX_COUNT];



/*
** Need to define the OS Module table here.
** osconfig.h will have the maximum number of loadable modules defined.
*/
OS_module_record_t OS_module_table[OS_MAX_MODULES];

/*
** The Mutex for protecting the above table
*/
SemaphoreHandle_t OS_module_table_mut;



int32 OS_ModuleTableInit( void )
{
    unsigned int i;

    /*
    ** Initialize Module Table
    */
    for(i = 0; i < OS_MAX_MODULES; ++i)
    {
        OS_module_table[i].entry_point = 0;
        OS_module_table[i].host_module_id = 0;
        OS_module_table[i].addr.valid = FALSE;
        strcpy(OS_module_table[i].name,"");
        strcpy(OS_module_table[i].filename,"");
    }

    /*
    ** Create the Module Table mutex
    */
    OS_module_table_mut = xSemaphoreCreateMutex();
    if ( OS_module_table_mut != NULL )
    {
        return(OS_SUCCESS);
    }
    else
    {
        return(OS_ERROR);
    }
}



int32 OS_SymbolLookup(cpuaddr *symbol_address, const char *symbol_name )
{
    OS_printf("%s\n", __FUNCTION__);

	return OS_ERROR;
}



int32 OS_SymbolTableDump( const char *filename, uint32 size_limit )
{
    uint32 i;
    int32  status;
    uint32 fileSize = 0;
    int32  fd;

    if(filename == NULL)
    {
        return(OS_INVALID_POINTER);
    }

    fd = OS_creat(filename, OS_READ_WRITE);
    if(fd < 0)
    {
    	return OS_ERROR;
    }

    for(i = 0; i < OS_DL_EXPORT_MAX_COUNT; ++i)
    {
    	uint32 lineLength;
    	char   line[OS_DL_SYMTBL_MAX_LINE_LENGTH] = {0};

    	snprintf(line, OS_DL_SYMTBL_MAX_LINE_LENGTH, "%s,%08x\n",
    			OS_DL_Exports[i].sym_name,
    			OS_DL_Exports[i].sym_value);

    	lineLength = strnlen(line, OS_DL_SYMTBL_MAX_LINE_LENGTH);

    	xil_printf(line);

    	fileSize += lineLength;

        if(fileSize > size_limit)
        {
        	break;
        }

        status = OS_write(fd, line, lineLength);
        if(status != lineLength)
        {
        	OS_close(fd);
        	return OS_ERROR;
        }
    }

	OS_close(fd);
	return OS_SUCCESS;
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
    /*
    ** Check the parameter
    */
    if ( module_info == 0 )
    {
        return(OS_INVALID_POINTER);
    }

    /*
    ** Check the module_id
    */
    if ( module_id >= OS_MAX_MODULES )
    {
        return(OS_ERR_INVALID_ID);
    }

    /*
    ** Fill out the module info
    */
    module_info->entry_point = OS_module_table[module_id].entry_point;
    module_info->host_module_id = OS_module_table[module_id].host_module_id;
    strncpy(module_info->filename, OS_module_table[module_id].filename , OS_MAX_PATH_LEN);
    strncpy(module_info->name, OS_module_table[module_id].name, OS_MAX_API_NAME);

    /*
    ** Address info is currently not valid on Linux
    */
    module_info->addr.valid = FALSE;
    module_info->addr.code_address = 0;
    module_info->addr.code_size = 0;
    module_info->addr.data_address = 0;
    module_info->addr.data_size = 0;
    module_info->addr.bss_address = 0;
    module_info->addr.bss_size = 0;
    module_info->addr.flags = 0;

    return OS_SUCCESS;
}

