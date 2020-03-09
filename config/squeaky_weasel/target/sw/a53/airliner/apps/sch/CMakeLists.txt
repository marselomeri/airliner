set(APP_NAME sch)

add_airliner_app_unit_test_src(
    ${APP_NAME}
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/sch_custom_rt.c
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

add_airliner_app_unit_test(sch-custom-ut
    UTASSERT 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/sch_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/sch_custom_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/sch_test_utils.c
	${CMAKE_CURRENT_SOURCE_DIR}/sch_custom_rt.c
    INCLUDES
        $ENV{AIRLINER_ROOT}/apps/sch/fsw/src/
        $ENV{AIRLINER_ROOT}/apps/sch/fsw/public_inc/
)


