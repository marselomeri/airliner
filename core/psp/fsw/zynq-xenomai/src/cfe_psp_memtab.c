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
** Includes
*/

#include "common_types.h"
#include "osapi.h"
#include "cfe_psp.h"
#include "cfe_psp_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>


/*
** Defines
*/
#define EEPROM_FILE "EEPROM.DAT"

/*
** Valid memory map for this target.
** If you need to add more entries, increase CFE_PSP_MEM_TABLE_SIZE in the osconfig.h file.
*/
CFE_PSP_MemTable_t CFE_PSP_MemoryTable[CFE_PSP_MEM_TABLE_SIZE] = 
{
   { CFE_PSP_MEM_RAM, CFE_PSP_MEM_SIZE_DWORD, 0, 0xFFFFFFFF, CFE_PSP_MEM_ATTR_READWRITE },
   { CFE_PSP_MEM_INVALID, 0, 0, 0, CFE_PSP_MEM_ATTR_READWRITE },
   { CFE_PSP_MEM_INVALID, 0, 0, 0, CFE_PSP_MEM_ATTR_READWRITE },
   { CFE_PSP_MEM_INVALID, 0, 0, 0, CFE_PSP_MEM_ATTR_READWRITE },
   { CFE_PSP_MEM_INVALID, 0, 0, 0, CFE_PSP_MEM_ATTR_READWRITE },
   { CFE_PSP_MEM_INVALID, 0, 0, 0, CFE_PSP_MEM_ATTR_READWRITE },
   { CFE_PSP_MEM_INVALID, 0, 0, 0, CFE_PSP_MEM_ATTR_READWRITE },
   { CFE_PSP_MEM_INVALID, 0, 0, 0, CFE_PSP_MEM_ATTR_READWRITE },
   { CFE_PSP_MEM_INVALID, 0, 0, 0, CFE_PSP_MEM_ATTR_READWRITE },
   { CFE_PSP_MEM_INVALID, 0, 0, 0, CFE_PSP_MEM_ATTR_READWRITE },
};

/*
** Simulate EEPROM by mapping in a file
*/
int32 CFE_PSP_SetupEEPROM(uint32 EEPROMSize, uint32 *EEPROMAddress)
{
   
/*   int          FileDescriptor;
   int          ReturnStatus;
   char        *DataBuffer;
   struct stat  StatBuf;


   ** Check to see if the file has been created.
   ** If not, create it.
   ** If so, then open it for read/write

   ReturnStatus = stat(EEPROM_FILE, &StatBuf);
   if ( ReturnStatus == -1 )
   {

      ** File does not exist, create it.

      FileDescriptor = open(EEPROM_FILE, O_RDWR | O_CREAT, S_IRWXU);
      if ( FileDescriptor == -1 )
      {
         OS_printf("CFE_PSP: Cannot open EEPROM File: %s\n",EEPROM_FILE);
         return(-1);
      }
      else
      {

         ** Need to seek to the desired EEPROM size

         if (lseek (FileDescriptor, EEPROMSize - 1, SEEK_SET) == -1)
         {
            OS_printf("CFE_PSP: Cannot Seek to end of EEPROM file.\n");
            close(FileDescriptor);
            return(-1);
         }


         ** Write a byte at the end of the File

         if (write (FileDescriptor, "", 1) != 1)
         {
            OS_printf("CFE_PSP: Cannot write to EEPROM file\n");
            close(FileDescriptor);
            return(-1);
         }
      }
   }
   else
   {

      ** File exists

      FileDescriptor = open(EEPROM_FILE, O_RDWR);
      if ( FileDescriptor == -1 )
      {
         OS_printf("CFE_PSP: Cannot open EEPROM File: %s\n",EEPROM_FILE);
         perror("CFE_PSP: open");
         return(-1);
      }
   }


   ** Map the file to a memory space

   if ((DataBuffer = mmap((caddr_t)0, EEPROMSize, PROT_READ | PROT_WRITE, MAP_SHARED, FileDescriptor, 0)) == (caddr_t)(-1))
   {
      OS_printf("CFE_PSP: mmap to EEPROM File failed\n");
      close(FileDescriptor);
      return(-1);
   }


   ** Return the address to the caller

   *EEPROMAddress = (uint32)DataBuffer;*/
   
   return(0);
}
