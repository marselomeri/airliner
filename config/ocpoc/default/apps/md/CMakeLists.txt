set(APP_NAME md)

add_airliner_app_src(
    ${APP_NAME}
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/md_custom.c
)

add_airliner_app_table(
    ${APP_NAME}
    NAME md_dw1_tbl
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/md_dw1_tbl.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME md_dw2_tbl
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/md_dw2_tbl.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME md_dw3_tbl
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/md_dw3_tbl.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

add_airliner_app_table(
    ${APP_NAME}
    NAME md_dw4_tbl
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/md_dw4_tbl.c
    INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
