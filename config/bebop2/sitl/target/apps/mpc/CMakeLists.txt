set(APP_NAME mpc)

add_airliner_app_table(
    ${APP_NAME}
    NAME mpc_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mpc_config.c
)

target_sources(${APP_NAME}-ut PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tables/mpc_config.c)
