set(APP_NAME sg33bl)

add_airliner_app_table(
    ${APP_NAME}
    NAME sg33bl_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/sg33bl_config.c
)
