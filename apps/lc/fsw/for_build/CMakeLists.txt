
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

add_airliner_app_unit_test(lc-ut
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_utest_adt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_utest_wdt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_utest.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../tables/lc_def_adt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../tables/lc_def_wdt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_action.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_cmds.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/lc_watch.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_cds.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_esmempool.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_evs.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_eeprom.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memory.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memrange.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_memutils.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_port.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_ram.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_support.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_sb_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_sb.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_tbl_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_tbl_internal.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_time_api.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_time_utils.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osapi.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfileapi.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfilesys.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osloader.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_ostimer.c
        ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_sim.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/sb/ccsds.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/sb/cfe_sb_util.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/es/cfe_es_cds_mempool.c
        ${PROJECT_SOURCE_DIR}/cfe/fsw/src/fs/cfe_fs_api.c
        ${PROJECT_SOURCE_DIR}/psp/fsw/pc-linux/src/cfe_psp_timer.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PROJECT_SOURCE_DIR}/tools/utf/inc/
        
    UTF_OUTPUT_FILE
        ${CMAKE_CURRENT_BINARY_DIR}/lc_utest.out
        
    UTF_BLESSED_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/lc_utest.out
)