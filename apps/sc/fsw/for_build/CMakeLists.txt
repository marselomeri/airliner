
add_airliner_app_def(sc
    FILE SC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_atsrq.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_atsrq.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_loads.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_loads.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_msgdefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_rtsrq.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_rtsrq.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_state.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_state.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_verify.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)



add_airliner_app_unit_test(sc-ut
    NO_MEMCHECK
    NO_HELGRIND
    NO_MASSIF
    UTASSERT 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_atsrq_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_atsrq_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_loads_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_loads_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_rtsrq_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_rtsrq_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_state_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_state_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_atsrq.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_atsrq.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_cmds.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_loads.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_loads.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_msgdefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_rtsrq.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_rtsrq.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_state.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_state.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_verify.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../mission_inc/sc_perfids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../platform_inc/sc_msgids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../platform_inc/sc_platform_cfg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../platform_inc/sc_rts.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${CMAKE_CURRENT_SOURCE_DIR}/../mission_inc/
        ${CMAKE_CURRENT_SOURCE_DIR}/../platform_inc/
)