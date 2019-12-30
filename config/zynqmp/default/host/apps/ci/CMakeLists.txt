set(APP_NAME ci)

add_airliner_app_table(
    ${APP_NAME}
    NAME ci_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ci_config.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_unit_test_src(${APP_NAME} SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ci_config.c)

add_airliner_app_unit_test(ci-custom-ut
    UTASSERT 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ci_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ci_custom_test.c
	    ${CMAKE_CURRENT_SOURCE_DIR}/ci_custom.c
        ${PROJECT_SOURCE_DIR}/apps/ci/fsw/src/ci_app.c
        ${PROJECT_SOURCE_DIR}/apps/ci/fsw/src/ci_cds_utils.c
        ${PROJECT_SOURCE_DIR}/apps/ci/fsw/src/ci_config_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ci_mock_os_calls.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ci_test_utils.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_es_hooks.c
        ${PROJECT_SOURCE_DIR}/apps/pblib/fsw/src/pb_lib.c
        
	INCLUDES
        ${PROJECT_SOURCE_DIR}/apps/ci/fsw/src/
        
    WRAPPERS
        socket
        bind
    
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ci-custom.supp
)
