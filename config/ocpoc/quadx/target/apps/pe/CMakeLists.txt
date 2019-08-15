set(APP_NAME pe)

add_airliner_app_table(
    ${APP_NAME}
    NAME pe_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/pe_config.c
)

add_airliner_app_unit_test_src(${APP_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/tables/pe_config.c)
