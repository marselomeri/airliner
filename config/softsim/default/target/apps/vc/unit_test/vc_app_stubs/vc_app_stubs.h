#ifndef VC_APP_STUBS_H
#define VC_APP_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cfe.h"

boolean VC_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen);

#ifdef __cplusplus
}
#endif

#endif /* VC_APP_STUBS_H */
