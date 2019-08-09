set(APP_NAME qae)

add_airliner_app_table(
    ${APP_NAME}
    NAME qae_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/qae_config.c
)

psp_add_custom_source_to_unit_tests(${APP_NAME} SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/qae_config.c)
