
add_airliner_app_def(pmc
    FILE PMC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pmc_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pmc_cds_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pmc_config_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pmc_config_utils.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${PX4_MSGS_DIR}
)

#add_airliner_app_unit_test(PMC-UT
#    UTASSERT
#    SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pmc_app_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pmc_cds_tbl_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pmc_cmds_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pmc_config_tbl_test.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pmc_testrunner.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/pmc_test_utils.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pmc_app.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pmc_cds_utils.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/pmc_config_utils.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../../mixer/fsw/src/mixer.c
#        
#    INCLUDES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
#        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
#)
