
add_airliner_app_def(qae
    FILE QAE
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_app.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix3F3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix3F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix4F4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix4F4.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Quaternion.hpp
   
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/

    USER_DOCS   ${CMAKE_CURRENT_SOURCE_DIR}/user_doxy.in
    DESIGN_DOCS ${CMAKE_CURRENT_SOURCE_DIR}/detail_doxy.in
)

add_airliner_app_unit_test(qae-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_app_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_cmds_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_config_tbl_test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/qae_test_utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_app.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/qae_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix3F3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix3F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix4F4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix4F4.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Quaternion.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/valgrind.supp
)
