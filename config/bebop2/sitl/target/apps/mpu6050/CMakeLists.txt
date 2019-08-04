set(APP_NAME mpu6050)

add_airliner_app_table(
    ${APP_NAME}
    NAME mpu6050_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mpu6050_config.c
)

psp_add_custom_source_to_unit_tests(${APP_NAME} SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/mpu6050_config.c)
