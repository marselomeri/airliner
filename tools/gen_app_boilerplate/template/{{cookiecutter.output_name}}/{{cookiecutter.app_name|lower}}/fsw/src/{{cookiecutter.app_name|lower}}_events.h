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

{{cookiecutter.app_name|lower}}_events.h
*/

/* Event message ID's */
#define {{cookiecutter.app_name}}_INIT_INF_EID       1  /* start up message "informational" */
#define {{cookiecutter.app_name}}_NOOP_INF_EID       2  /* processed command "informational" */
#define {{cookiecutter.app_name}}_RESET_INF_EID      3
#define {{cookiecutter.app_name}}_PROCCESS_INF_EID   4
#define {{cookiecutter.app_name}}_MID_ERR_EID        5  /* invalid command packet "error" */
#define {{cookiecutter.app_name}}_CC1_ERR_EID        6
#define {{cookiecutter.app_name}}_LEN_ERR_EID        7
#define {{cookiecutter.app_name}}_PIPE_ERR_EID       8
#define {{cookiecutter.app_name}}_EVT_COUNT          8  /* count of event message ID's */
