set(APP_NAME ea)

add_airliner_app_table(
    ${APP_NAME}
    NAME ea_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ea_config.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_unit_test(ea-custom-ut
    UTASSERT 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ea_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ea_custom_test.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/ea_custom.c
        ${PROJECT_SOURCE_DIR}/apps/ea/fsw/src/ea_app.c
        ${PROJECT_SOURCE_DIR}/apps/ea/fsw/src/ea_cds_utils.c
        ${PROJECT_SOURCE_DIR}/apps/ea/fsw/src/ea_config_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ea_mock_os_calls.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ea_test_utils.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_es_hooks.c
        
	INCLUDES
        ${PROJECT_SOURCE_DIR}/apps/ea/fsw/src/
)

add_airliner_app_unit_test(ea-perfmon-ut
    UTASSERT 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ea_perfmon_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ea_perfmon_test.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/ea_custom.c
        ${PROJECT_SOURCE_DIR}/apps/ea/fsw/src/ea_app.c
        ${PROJECT_SOURCE_DIR}/apps/ea/fsw/src/ea_cds_utils.c
        ${PROJECT_SOURCE_DIR}/apps/ea/fsw/src/ea_config_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/ea_test_utils.c
        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_es_hooks.c
        
	INCLUDES
        ${PROJECT_SOURCE_DIR}/apps/ea/fsw/src/
)

set_property(TARGET ea-custom-ut
        APPEND_STRING
        PROPERTY
        LINK_FLAGS
        "-Wl,--wrap=fork \
		 -Wl,--wrap=execvp \
		 -Wl,--wrap=waitpid \
		 -Wl,--wrap=kill"
)

add_custom_target(
    ea-ut-input-files
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/sleep.py ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/fib.py ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/noop.py ${CMAKE_CURRENT_BINARY_DIR}
)

add_dependencies(ea-custom-ut ea-ut-input-files)
add_dependencies(ea-perfmon-ut ea-ut-input-files)
