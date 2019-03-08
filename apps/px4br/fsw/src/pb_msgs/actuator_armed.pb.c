/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.6 at Wed Oct 26 00:46:06 2016. */

#include "actuator_armed.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t px4_actuator_armed_pb_fields[8] = {
    PB_FIELD(  1, UINT64  , REQUIRED, STATIC  , FIRST, px4_actuator_armed_pb, timestamp, timestamp, 0),
    PB_FIELD(  2, BOOL    , REQUIRED, STATIC  , OTHER, px4_actuator_armed_pb, armed, timestamp, 0),
    PB_FIELD(  3, BOOL    , REQUIRED, STATIC  , OTHER, px4_actuator_armed_pb, prearmed, armed, 0),
    PB_FIELD(  4, BOOL    , REQUIRED, STATIC  , OTHER, px4_actuator_armed_pb, ready_to_arm, prearmed, 0),
    PB_FIELD(  5, BOOL    , REQUIRED, STATIC  , OTHER, px4_actuator_armed_pb, lockdown, ready_to_arm, 0),
    PB_FIELD(  6, BOOL    , REQUIRED, STATIC  , OTHER, px4_actuator_armed_pb, force_failsafe, lockdown, 0),
    PB_FIELD(  7, BOOL    , REQUIRED, STATIC  , OTHER, px4_actuator_armed_pb, in_esc_calibration_mode, force_failsafe, 0),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */