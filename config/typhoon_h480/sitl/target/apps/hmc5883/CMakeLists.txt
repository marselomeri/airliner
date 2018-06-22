set(APP_NAME hmc5883)

add_airliner_app_table(
    ${APP_NAME}
    NAME hmc5883_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/hmc5883_config.c
)
