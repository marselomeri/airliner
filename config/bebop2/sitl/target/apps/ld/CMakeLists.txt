set(APP_NAME ld)

add_airliner_app_table(
    ${APP_NAME}
    NAME ld_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ld_config.c
)
