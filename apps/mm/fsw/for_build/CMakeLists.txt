
add_airliner_app_def(mm
    FILE MM
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_dump.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_load.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem16.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem8.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_utils.c
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
)

add_airliner_app_unit_test(MM-UT
    UTF 
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_app_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_dump_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_load_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_mem16_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_mem32_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_mem8_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_testrunner.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_test_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mm_utils_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_app.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_dump.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_load.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem16.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem32.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_mem8.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mm_utils.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../cfs_lib/fsw/src/cfs_utils.c
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
)

## Generate documentation
#find_package(Doxygen)
#if(DOXYGEN_FOUND)
#    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in ${CMAKE_CURRENT_BINARY_DIR}/user_doxy @ONLY)
#    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in ${CMAKE_CURRENT_BINARY_DIR}/detail_doxy @ONLY)
#    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/codewalk_doxy.in ${CMAKE_CURRENT_BINARY_DIR}/codewalk_doxy @ONLY)
#    add_custom_target(sch-docs
#        COMMENT "Generating API documentation with Doxygen" VERBATIM
#    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/users_guide/html/${APPTARGET}/
#    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/users_guide/latex/${APPTARGET}/
#    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/detailed_design/html/${APPTARGET}/
#    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/detailed_design/latex/${APPTARGET}/
#    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/cwt/html/${APPTARGET}/
#    	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/docs/cwt/latex/${APPTARGET}/
#        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/user_doxy
#        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/detail_doxy
#        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/codewalk_doxy
#        #COMMAND make -C ${CMAKE_BINARY_DIR}/docs/users_guide/latex/${APPTARGET}
#        #COMMAND make -C ${CMAKE_BINARY_DIR}/docs/detailed_design/latex/${APPTARGET}
#        #COMMAND make -C ${CMAKE_BINARY_DIR}/docs/cwt/latex/${APPTARGET}
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
#    )
#endif(DOXYGEN_FOUND)
