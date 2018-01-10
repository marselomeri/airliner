set(APP_NAME params)

add_airliner_app_table(
    ${APP_NAME}
    NAME params_table
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/params_table.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

