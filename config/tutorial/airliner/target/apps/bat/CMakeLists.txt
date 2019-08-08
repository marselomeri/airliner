set(APP_NAME bat)

add_airliner_app_table(
    ${APP_NAME}
    NAME bat_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/bat_config.c
)

psp_add_custom_source_to_unit_tests(${APP_NAME} SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/bat_config.c)

