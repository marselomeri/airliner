#ifndef MFAB_PUBLIC_MSGS_H
#define MFAB_PUBLIC_MSGS_H

#include "cfe.h"



typedef struct
{
    uint8  ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    float  rawValue;
} MFAB_RawValueMsg_t;


#endif
