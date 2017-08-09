
add_airliner_app_def(sc
    FILE SC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_atsrq.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_loads.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_rtsrq.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_state.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_utils.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)



add_airliner_app_unit_test(sc-ut
    UTASSERT 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_atsrq_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_loads_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_rtsrq_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_state_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sc_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_atsrq.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_loads.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_rtsrq.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_state.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sc_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)