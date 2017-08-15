
add_airliner_app_def(sch
    FILE SCH
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_api.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_app.c 
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_cmds.c 
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(sch-ut
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_api.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_app.c 
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_cmds.c 
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_custom.c 
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sch_api_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sch_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sch_cmds_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sch_custom_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sch_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/sch_testrunner.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/utassert.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_es_hooks.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_es_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_evs_hooks.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_fs_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_eeprom_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_memrange_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_memutils_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_ram_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_timer_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_watchdog_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_sb_hooks.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_tbl_hooks.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_tbl_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_time_hooks.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/utlist.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_osapi_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_osfileapi_stubs.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/uttest.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/uttools.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../mission_inc/
        ${CMAKE_CURRENT_SOURCE_DIR}/../platform_inc/
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/inc/
)