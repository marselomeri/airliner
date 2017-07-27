/*==============================================================================
Copyright (c) 2015, Windhover Labs
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of CmdIn nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

{{cookiecutter.app_name|lower}}_msg.h
*/

#include "cfe.h"

/* Example command packet command codes */
#define {{cookiecutter.app_name}}_NOOP_CC            0  /* no-op command */
#define {{cookiecutter.app_name}}_RESET_CC           1  /* reset counters */
#define {{cookiecutter.app_name}}_HELLOWORLD_CC      2  /* hello world command */

/* Type definition (generic "no arguments" command) */
typedef struct
{
    uint8                 CmdHeader[CFE_SB_CMD_HDR_SIZE];
} {{cookiecutter.app_name}}_NoArgsCmd_t;


/* Type definition ({{cookiecutter.app_name}} housekeeping) */
typedef struct
{
    uint8                 TlmHeader[CFE_SB_TLM_HDR_SIZE];

    /* Command interface counters */
    uint8                 CmdCounter;
    uint8                 ErrCounter;
} {{cookiecutter.app_name}}_HkPacket_t;
