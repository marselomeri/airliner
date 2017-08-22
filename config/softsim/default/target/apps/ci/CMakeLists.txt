set(APP_NAME ci)

add_airliner_app_table(
    ${APP_NAME}
    NAME ci_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ci_config.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME ci_timeout
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ci_timeout.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_unit_test_src(
    ci-ut
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ci_custom.c
)

