
add_airliner_app_def(sch
    FILE SCH
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_api.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_app.c 
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_cmds.c 
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

