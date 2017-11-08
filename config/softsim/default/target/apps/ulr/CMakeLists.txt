set(APP_NAME ulr)

add_airliner_app_table(
    ${APP_NAME}
    NAME ulr_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ulr_config.c
)
