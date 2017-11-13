
add_airliner_app_def(mpu9250
    FILE MPU9250
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_version.h
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(mpu9250-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mpu9250_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mpu9250_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mpu9250_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mpu9250_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mpu9250_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mpu9250_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mpu9250_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mpu9250_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mpu9250_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_app.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mpu9250_version.h
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
