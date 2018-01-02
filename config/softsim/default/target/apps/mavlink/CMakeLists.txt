set(APP_NAME mavlink)

add_airliner_app_table(
    ${APP_NAME}
    NAME mavlink_action
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mavlink_action.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

