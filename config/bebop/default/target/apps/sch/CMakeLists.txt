set(APP_NAME sch)

add_airliner_app_unit_test_src(
    ${APP_NAME}-ut
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/sch_custom.c
)

add_airliner_app_table(
    ${APP_NAME}
    NAME sch_def_schtbl
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/sch_def_schtbl.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME sch_def_msgtbl
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/sch_def_msgtbl.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

#add_airliner_app_unit_test(sch-custom-ut
#    UTASSERT 
#    SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/sch_testrunner.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/sch_custom_test.c
#        #${CMAKE_CURRENT_SOURCE_DIR}/unit_test/sch_mock_os_calls.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/sch_test_utils.c
#	    ${CMAKE_CURRENT_SOURCE_DIR}/sch_custom.c
##        ${PROJECT_SOURCE_DIR}/apps/sch/fsw/src/sch_app.c
##        ${PROJECT_SOURCE_DIR}/apps/sch/fsw/src/sch_cds_utils.c
##        ${PROJECT_SOURCE_DIR}/apps/sch/fsw/src/sch_config_utils.c
##        ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_es_hooks.c
#        
#	INCLUDES
#        ${PROJECT_SOURCE_DIR}/apps/sch/fsw/src/
#        
##    WRAPPERS
##        socket
##        bind
#    
#)


