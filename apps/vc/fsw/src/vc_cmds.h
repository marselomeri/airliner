#include "cfe.h"

/**
 * \brief On-board command (HK request)
 */
void VC_HousekeepingCmd(CFE_SB_MsgPtr_t msg);


/**
 * \brief ground command (NO-OP)
 */
void VC_NoopCmd(CFE_SB_MsgPtr_t msg);


/**
 * \brief ground command (reset counters)
 */
void VC_ResetCmd(CFE_SB_MsgPtr_t msg);


/**
 * \brief ground command (hello world command)
 */
void VC_HelloWorldCmd(CFE_SB_MsgPtr_t msg); 


/**
 * \brief Verify command packet length
 */
boolean VC_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength); 
