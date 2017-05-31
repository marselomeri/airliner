set(APP_NAME cf)

add_airliner_app_table(
    ${APP_NAME}
    NAME cf_cfgtable
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/cf_cfgtable.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)


