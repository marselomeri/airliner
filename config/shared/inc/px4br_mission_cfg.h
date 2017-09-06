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

* Neither the name of TlmOut nor the names of its
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
*/
    
#ifndef _PX4BR_MISSION_CFG_H_
#define _PX4BR_MISSION_CFG_H_

/*
** Pragmas
*/

/*
** Local Defines
*/

/*
** Include Files
*/


/*
** Local Structure Declarations
*/

/*
 * Defines
 */
#define PX4BR_HEARTBEAT_SEND_PERIOD			1000
#define PX4BR_HEARTBEAT_TASK_NAME_TEMPLATE	"PX4BR_HB_"
#define PX4BR_HEARTBEAT_TASK_STACK_SIZE 	24576
#define PX4BR_HEARTBEAT_TASK_PRIORITY		120
#define PX4BR_HEARTBEAT_SEND_DELAY       	1000

#define PX4BR_LISTENER_TASK_NAME_TEMPLATE	"PX4BR_LST_"
#define PX4BR_LISTENER_TASK_STACK_SIZE 	24576
#define PX4BR_LISTENER_TASK_PRIORITY		120
#define PX4BR_LISTENER_SEND_DELAY       	1000

#define PX4BR_DATAOUT_TASK_NAME_TEMPLATE	"PX4BR_DO_"
#define PX4BR_DATAOUT_TASK_STACK_SIZE 		24576
#define PX4BR_DATAOUT_TASK_PRIORITY			120
#define PX4BR_DATAOUT_SEND_DELAY       		1000

/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/

#endif /* _PX4BR_MISSION_CFG_H_ */

/*=======================================================================================
** End of file eta_mission_cfg.h
**=====================================================================================*/
    
