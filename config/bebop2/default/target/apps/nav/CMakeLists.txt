set(APP_NAME nav)

add_airliner_app_table(
    ${APP_NAME}
    NAME nav_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/nav_config.c
)

psp_add_custom_source_to_unit_tests(${APP_NAME} SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/nav_config.c)
