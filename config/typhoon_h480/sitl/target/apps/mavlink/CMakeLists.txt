set(APP_NAME mavlink)

add_airliner_app_table(
    ${APP_NAME}
    NAME mavlink_param
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mavlink_param.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

