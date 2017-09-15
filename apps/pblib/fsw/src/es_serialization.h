#ifndef SRC_ES_SERIALIZATION_H_
#define SRC_ES_SERIALIZATION_H_
#endif

#include "cfe.h"
#include "cfe_es_msg.h"

#include "../../../../tools/nanopb/pb_encode.h"
#include "../../../../tools/nanopb/pb_decode.h"
#include "es_log.pb.h"

/* Serialization Functions */
uint32 CFE_ES_OverWriteSysLogCmd_t_Enc(const CFE_ES_OverWriteSysLogCmd_t *inObject, char *inOutBuffer, uint32 inSize);
uint32 CFE_ES_OverWriteSysLogCmd_t_Dec(const char *inBuffer, uint32 inSize, CFE_ES_OverWriteSysLogCmd_t *inOutObject);
