
add_airliner_app_def(vc
    FILE VC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/vc_cmds.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
)
