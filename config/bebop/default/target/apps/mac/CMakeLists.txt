set(APP_NAME mac)

add_airliner_app_table(
    ${APP_NAME}
    NAME mac_param
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mac_param.c
)
