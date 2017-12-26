set(APP_NAME mpc)

add_airliner_app_table(
    ${APP_NAME}
    NAME mpc_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mpc_config.c
)
