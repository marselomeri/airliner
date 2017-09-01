set(APP_NAME hk)

add_airliner_app_table(
    ${APP_NAME}
    NAME hk_cpy_tbl
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/hk_cpy_tbl.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)


