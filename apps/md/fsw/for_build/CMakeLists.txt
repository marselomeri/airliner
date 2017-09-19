
add_airliner_app_def(md
    FILE MD
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_pkt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_pkt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_tbl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_tbl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_msgdefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_verify.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)


add_airliner_app_unit_test(md-ut 
    UTASSERT
        
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_pkt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_pkt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_tbl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_tbl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_msgdefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_verify.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_dwell_pkt_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_dwell_pkt_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_dwell_tbl_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_dwell_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_utils_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/md_utils_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../cfs_lib/fsw/src/cfs_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)