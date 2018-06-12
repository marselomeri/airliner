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
/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "sonar_bebop.h"
#include "sonar_events.h"
#include "sonar_perfids.h"

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/************************************************************************
** External Global Variables
*************************************************************************/

/************************************************************************
** Global Variables
*************************************************************************/
SONAR_AppCustomData_t SONAR_AppCustomData;

/************************************************************************
** Local Variables
*************************************************************************/

/************************************************************************
** Local Function Definitions
*************************************************************************/

int SONAR_ADC_Enable(void)
{
    /* Set the device path. */
    snprintf(SONAR_AppCustomData.ADCDevicePath, sizeof(SONAR_AppCustomData.ADCDevicePath), SONAR_ADC_DEVICE_PATH);

    /* Before we setup the device, disable the pin (prevent resource busy error). */
    SONAR_ADC_Disable();

    /* Enable the channel. */
    SONAR_ADC_Write(SONAR_ADC_CHANNEL, 1);

    /* Set buffer length and disable it initially. */
    SONAR_ADC_Write("/buffer/length", SONAR_BUFFER_LEN);

    SONAR_AppCustomData.BufferEnabled = TRUE;

    return SONAR_ADC_Write("buffer/enable", 1);
}


int SONAR_ADC_Disable(void)
{
    SONAR_AppCustomData.BufferEnabled = FALSE;

    return SONAR_ADC_Write("buffer/enable", 0);
}


int SONAR_ADC_Read(uint16 *buffer, uint16 length)
{
    int returnVal = -1;
    FILE *file;
    char path[20];

    if(FALSE == SONAR_AppCustomData.BufferEnabled)
    {
        goto end_of_function;
    }

    if(0 == buffer)
    {
        goto end_of_function;
    }

    snprintf(path, sizeof(path), "/dev/iio:device0");

    file = fopen(path, "r");

    if(0 == file)
    {
        goto end_of_function;
    }

    returnVal = fread(buffer, 2 len, file);
    if(returnVal < 0)
    {
        goto end_of_function;
    }

    returnVal = fclose(file);
    if(returnVal < 0)
    {
        goto end_of_function;
    }

end_of_function:
    return returnVal;
}


int SONAR_ADC_Write(const char *path, int value)
{
    int returnVal = -1;
    char filename[sizeof(SONAR_AppCustomData.ADCDevicePath) + 20] = {0};
    FILE *file;

    snprintf(filename, sizeof(filename), "%s/%s", SONAR_AppCustomData.ADCDevicePath, path);

    file = fopen(filename, "w");
    if(0 == file)
    {
        goto end_of_function;
    }

    fprintf(file, "%d", value);

    returnVal = fclose(file);
    if(returnVal < 0)
    {
        goto end_of_function;
    }

end_of_function:
    return returnVal;
}

