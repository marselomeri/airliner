set(APP_NAME qae)

add_airliner_app_table(
    ${APP_NAME}
    NAME qae_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/qae_config.c
)
