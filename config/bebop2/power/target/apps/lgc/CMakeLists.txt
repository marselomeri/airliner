set(APP_NAME lgc)

add_airliner_app_table(
    ${APP_NAME}
    NAME lgc_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/lgc_config.c
)
