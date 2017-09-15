
add_airliner_app_def(lc
    FILE LC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_action.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_action.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_custom.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_msgdefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_tbl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_verify.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_watch.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_watch.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(lc-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_action.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_action.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_custom.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_msgdefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_tbl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_verify.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_watch.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_watch.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_action_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_action_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_custom_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_custom_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_watch_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_watch_test.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)