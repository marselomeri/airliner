set(APP_NAME md)

add_airliner_app_table(
    ${APP_NAME}
    NAME md_dw01
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/md_dw01.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME md_dw02
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/md_dw02.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME md_dw03
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/md_dw03.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME md_dw04
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/md_dw04.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
