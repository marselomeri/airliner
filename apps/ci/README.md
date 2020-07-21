# Command Ingestion

***
## Table of Contents

* [CI Acronyms](#ci-acronyms)
* [CI Overview](#ci-overview)
  * [CI Activities](#ci-activities)
  * [CI Structure](#ci-structure)
* [CI Documentation](#ci-documentation)
  * [CI Operation](#ci-operation:)
  * [CI Requirements](#ci-requirements:)
  * [CI Deployment Guide](#ci-deployment-guide:)
  * [CI Commands](#ci-commands:)
  * [CI Tememetry](#ci-telemetry:)
  * [CI Table Definitions](#ci-table-definitions:)
  * [CI Configuration Parameters](#ci-configuration-parameters:)
  * [CI Operational Constraints](#ci-operational-constraints:)
  * [CI FAQs](#ci-faqs:)
  * [CI Event Message Reference](#ci-event-message-reference:)
***
## CI Acronyms

The following table provides complete specification for the commands and telemetry associated with the CI Application (CI)software:

|acronym| description						 |
|API	|Application Programming Interface			 |
|CCSDS	|Consultative Committee for Space Data Systems		 |
|C&DH	|Command and Data Handling				 |
|CFE	|Core Flight Executive					 |
|CFS	|Core Flight System					 |
|Cmd	|Command						 |
|CPU	|Central Processing Unit				 |
|FSW	|Flight Software					 |
|HK	|Housekeeping telemetry, or CFS House Keeping Application|
|HW,H/W	|Hardware						 |
|ICD	|Interfacce Control Document				 |
|ISR	|Interrupt Service Routine				 |
|OS	|Operating System					 |
|OSAL	| Operating System Abstraction Layer			 |
|Pkts	|packets						 |
|RAM 	|Random-Access Memory					 |
|RTOS	|Real Time Operating System				 |
|SB	|Software Bus Service					 |
|SW,S/W	|software						 |
|TBD	|To Be Determined					 |
|TBL	|Table							 |
|TLM	|Telemetry						 |
|UTC	|Universal Coordinated Time(time scale)			 |

***
## CI Overview

The CI application can do some cool stuff

![CI Diagram]()

### CI Activities

Process Commands

### CI Structure



## CI Documention



### CI Operation
1. The application version number

The application version number is displayed in the initialization event and the no-op event.
2. Table Handling

TODO High-level stuff on tables goes here.
3. Sending the No-op Command

TODO Discuss the No-Op command here.
4. Sending the reset counters command

TODO Discuss the reset counters command here.
5. Monitoring the command counter

TODO Discuss the counter here.
6. Monitoring the command error counter

TODO Discuss the counter behavior here.

[CI_Operation.md](docs/CI_Operation.md "Link to CI_Operations")


### CI Requirements

The following are CI application requirements
[CI_Requirements.md](docs/CI_Requirements.md "Link to TO Requirements")

### Deployment Guide

[CI_Deployment_Guide.md](docs/CI_Deployment_Guide.md "Link to CI Deployment Guide")

#### **Initial Integration**
The first step in deploying the CI application is to do stuff.
Application Tailoring to the Mission

#### **Application Tailoring to the Mission**
The ci_mission_cfg.h file, the ci_msgids.h, and the ci_perfids.h files are tailored for the mission. These are built into the application during compilation.
Application Tailoring to the Platform

#### **Application Tailoring to the Platform**
In the ci_platform_cfg.h file, there are configuration parameters that control CI application behavior. This should be tailored to the specific platform needs. This behavior is built into the application during compilation.
CFS Scheduler Support

#### **CFS Scheduler Support***
TODO Discuss any commands that must be included in the CFS Scheduler Table and any related tailoring/configuration.


### CI Commands

The following is a list of commands that are processed by the CI Application:

Global `CI_AUTH_CMD_CC`
    Authorize Command 

Global `CI_DEAUTH_CMD_CC`
    Deauthorize Command 

Global `CI_DEREG_CMD_CC`
    Deregister Command 

Global `CI_NOOP_CC`
    Noop 

Global `CI_REG_CMD_CC`
    Register Command 

Global `CI_RESET_CC`
    Reset Counters 

Global `CI_UPDT_CMD_CC`
    Update Command Registration 

[CI_Commands.md](docs/CI_Commands.md "Link to CI Commands")

### CI Telemetry

[CI_Telemetry.md](docs/CI_Telemtry.md "Link to CI Telemetry")

### CI Table Definitions

[CI_Table_Definitions.md](docs/CI_Table_Definitions.md "Link to CI Table Definitions")

### CI Configuration Parameters

[CI_Configuration_Parameters.md](docs/CI_Configuration_Parameters.md "Link to CI Configuration Parameters")

### CI Operational Constraints

[CI_Operational_Constraints.md](docs/CI_Operational_Constraints.md "Link to CI Operational Constraints")

#### **Application Termination**

Potential causes for CI to terminate prematurely are an error return from the software bus in the application 
main loop or error return from one of the cFE table services functions when CI tries to do table management
(check for updates, dump requests etc.) during each housekeeping cycle.

#### **Critical Data Store Operation**

When using the Critical Data Store (CDS), the results tables and housekeeping data will only be restored if the 
application was shut down through cFE Executive Services and exited clean. If this is not the case, default values
will be used (see CI Application Frequently Asked Questions).

### CI Frequently asked questions

[CI_FAQs.md](docs/CI_FAQs.md "Link to CI FAQs")
**General**

1. What is the basic flow of the application?

The CI application uses a common application format. When the app starts, initialization is performed, then the app 
enters an infinite loop waiting for commands from the software bus. 

### CI Event Message Reference

[CI_Event_Message_Reference.md](docs/CI_Event_Message_Reference.md "Link to CI Event Message Reference")



