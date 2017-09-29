set(ES_PROTOBUF_MSGS_DIR ${CMAKE_CURRENT_BINARY_DIR}/msgs/protobuf)

add_airliner_app_def(pblib
    FILE PBLIB
	NANOPB
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb_lib.h
      	${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_serialization.h
      	${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_serialization.c
      	${ES_PROTOBUF_MSGS_DIR}/es_perf_start.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_perf_start.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_restart.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_restart.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_perf_set_filter_mask.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_perf_set_filter_mask.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_tlm_pool_stats.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_tlm_pool_stats.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_shell.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_shell.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_perf_stop.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_perf_stop.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_shell_packet.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_shell_packet.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_overwrite_sys_log.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_overwrite_sys_log.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_query_all.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_query_all.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_perf_set_trig_mask.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_perf_set_trig_mask.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_app_reload.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_app_reload.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_write_er_log.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_write_er_log.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_app_name.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_app_name.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_hk.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_hk.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_one_app.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_one_app.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_set_max_pr_count.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_set_max_pr_count.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_start_app.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_start_app.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_delete_cds.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_delete_cds.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_query_all_tasks.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_query_all_tasks.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_write_sys_log.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_write_sys_log.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_tlm_pool_stats_cmd.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_tlm_pool_stats_cmd.pb.c
        ${ES_PROTOBUF_MSGS_DIR}/es_dump_cds_reg.pb.h
        ${ES_PROTOBUF_MSGS_DIR}/es_dump_cds_reg.pb.c

    INCLUDES
        ${ES_PROTOBUF_MSGS_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
		${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

	PROTOBUF_DEFS
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_perf_start.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_restart.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_perf_set_filter_mask.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_tlm_pool_stats.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_shell.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_perf_stop.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_shell_packet.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_overwrite_sys_log.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_query_all.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_perf_set_trig_mask.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_app_reload.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_write_er_log.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_app_name.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_hk.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_one_app.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_set_max_pr_count.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_start_app.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_delete_cds.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_query_all_tasks.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_write_sys_log.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_tlm_pool_stats_cmd.proto
        ${CMAKE_CURRENT_SOURCE_DIR}/../msgs/proto_defs/es_dump_cds_reg.proto
        
    PROTOBUF_MSGS_DIR        
        ${ES_PROTOBUF_MSGS_DIR}

    # This application has a public include header.  Add it so all the other applications can access it.
    PUBLIC_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
)

add_airliner_app_unit_test(pblib-ut
    UTASSERT
	NANOPB
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_lib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pb_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/pb_lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pbl_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pbl_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pbl_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pbl_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pbl_testrunner.c


	INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
		${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

)

set(ES_PROTOBUF_MSGS_DIR ${ES_PROTOBUF_MSGS_DIR} PARENT_SCOPE)
