set(APP_NAME to)

add_airliner_app_table(
    ${APP_NAME}
    NAME to_ground
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/to_ground.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME to_ground_test
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/to_ground_test.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME to_onboard
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/to_onboard.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_unit_test(to-custom-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/to_app_custom_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/to_app_custom_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/to_custom_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/to_custom_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/to_custom_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/to_app_stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/to_app_stubs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/to_custom.c
        ${CMAKE_CURRENT_SOURCE_DIR}/to_custom_udp.h

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/unit_test/
        ${PROJECT_SOURCE_DIR}/apps/to/fsw/src
)
