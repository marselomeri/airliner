set(APP_NAME ulr)

#add_airliner_app_unit_test_src(
#    ${APP_NAME}
#    SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/ulr_custom.cpp
#)

add_airliner_app_table(
    ${APP_NAME}
    NAME ulr_config
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tables/ulr_config.c
)
