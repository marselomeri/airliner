
add_airliner_app_def(lc
    FILE LC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_action.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_watch.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

