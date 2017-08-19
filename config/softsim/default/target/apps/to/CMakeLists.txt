set(APP_NAME to)

add_airliner_app_table(
    ${APP_NAME}
    NAME to_ground
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/to_ground.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME to_onboard
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/to_onboard.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)