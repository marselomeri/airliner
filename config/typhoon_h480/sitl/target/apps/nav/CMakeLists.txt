set(APP_NAME nav)

add_airliner_app_table(
    ${APP_NAME}
    NAME nav_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/nav_config.c
)

add_airliner_app_unit_test_src(${APP_NAME} SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/nav_config.c)
