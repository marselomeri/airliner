/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.6 at Wed Oct 26 00:46:13 2016. */

#ifndef PB_MAVLINK_LOG_PB_H_INCLUDED
#define PB_MAVLINK_LOG_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _px4_mavlink_log_pb {
    uint64_t timestamp;
    char text[50];
    uint32_t severity;
/* @@protoc_insertion_point(struct:px4_mavlink_log_pb) */
} px4_mavlink_log_pb;

/* Default values for struct fields */

/* Initializer values for message structs */
#define px4_mavlink_log_pb_init_default          {0, "", 0}
#define px4_mavlink_log_pb_init_zero             {0, "", 0}

/* Field tags (for use in manual encoding/decoding) */
#define px4_mavlink_log_pb_timestamp_tag         1
#define px4_mavlink_log_pb_text_tag              2
#define px4_mavlink_log_pb_severity_tag          3

/* Struct field encoding specification for nanopb */
extern const pb_field_t px4_mavlink_log_pb_fields[4];

/* Maximum encoded size of messages (where known) */
#define px4_mavlink_log_pb_size                  69

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define MAVLINK_LOG_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif