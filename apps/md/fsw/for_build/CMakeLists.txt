
add_airliner_app_def(md
    FILE MD
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_pkt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_dwell_tbl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/md_utils.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
)

