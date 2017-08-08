
add_airliner_app_def(cs
    FILE CS
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_app_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_compute.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_eeprom_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_memory_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_table_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_table_processing.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_utils.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)



add_airliner_app_unit_test(cs-ut
    UTF 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/utf_test_cs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_app_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_compute.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_eeprom_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_memory_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_table_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_table_processing.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/cs_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)