set(APP_NAME qae)

add_airliner_app_table(
    ${APP_NAME}
    NAME qae_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/qae_config.c
)

add_airliner_app_unit_test_src(${APP_NAME} SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/qae_config.c)
