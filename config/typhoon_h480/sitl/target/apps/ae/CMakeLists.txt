set(APP_NAME ae)

add_airliner_app_table(
    ${APP_NAME}
    NAME ae_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ae_config.c
)
