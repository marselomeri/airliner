/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.6 at Wed Oct 26 00:46:14 2016. */

#ifndef PB_MISSION_RESULT_PB_H_INCLUDED
#define PB_MISSION_RESULT_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _px4_mission_result_pb {
    uint64_t timestamp;
    uint32_t instance_count;
    uint32_t seq_reached;
    uint32_t seq_current;
    uint32_t item_changed_index;
    uint32_t item_do_jump_remaining;
    bool valid;
    bool warning;
    bool reached;
    bool finished;
    bool stay_in_failsafe;
    bool flight_termination;
    bool item_do_jump_changed;
    bool mission_failure;
/* @@protoc_insertion_point(struct:px4_mission_result_pb) */
} px4_mission_result_pb;

/* Default values for struct fields */

/* Initializer values for message structs */
#define px4_mission_result_pb_init_default       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#define px4_mission_result_pb_init_zero          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define px4_mission_result_pb_timestamp_tag      1
#define px4_mission_result_pb_instance_count_tag 2
#define px4_mission_result_pb_seq_reached_tag    3
#define px4_mission_result_pb_seq_current_tag    4
#define px4_mission_result_pb_item_changed_index_tag 5
#define px4_mission_result_pb_item_do_jump_remaining_tag 6
#define px4_mission_result_pb_valid_tag          7
#define px4_mission_result_pb_warning_tag        8
#define px4_mission_result_pb_reached_tag        9
#define px4_mission_result_pb_finished_tag       10
#define px4_mission_result_pb_stay_in_failsafe_tag 11
#define px4_mission_result_pb_flight_termination_tag 12
#define px4_mission_result_pb_item_do_jump_changed_tag 13
#define px4_mission_result_pb_mission_failure_tag 14

/* Struct field encoding specification for nanopb */
extern const pb_field_t px4_mission_result_pb_fields[15];

/* Maximum encoded size of messages (where known) */
#define px4_mission_result_pb_size               57

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define MISSION_RESULT_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif