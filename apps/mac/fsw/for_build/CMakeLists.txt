#############################################################################
#
#   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name Windhover Labs nor the names of its 
#    contributors may be used to endorse or promote products derived 
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#############################################################################
 
 
add_airliner_app_def(mac
    FILE MAC
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_app.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_private_ids.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_private_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_version.h
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
        ${PX4_MSGS_DIR}
)

add_airliner_app_unit_test(MAC-UT
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_app_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_app_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_cmds_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_cmds_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_config_tbl_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_config_tbl_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_app.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_msg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_private_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_tbldefs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_version.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/mac_config_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Quaternion.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix3F3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix3F3.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac-ut.supp
)


add_airliner_app_unit_test(MAC-V3F-UT
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector3F_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector3F_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector3F_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector3F_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector3F_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac-v3f-ut.supp
)


add_airliner_app_unit_test(MAC-V4F-UT
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector4F_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector4F_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector4F_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector4F_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector4F_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac-v4f-ut.supp
)


add_airliner_app_unit_test(MAC-QUATERNION-UT
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Quaternion_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Quaternion_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Quaternion_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Quaternion_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Quaternion_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Quaternion.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix3F3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix3F3.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac-quaternion-ut.supp
)


add_airliner_app_unit_test(MAC-MATRIX3F3-UT
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix3F3_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix3F3_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix3F3_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix3F3_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix3F3_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix3F3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix3F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector3F.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac-matrix3f3-ut.supp
)


add_airliner_app_unit_test(MAC-MATRIX4F4-UT
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix4F4_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix4F4_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix4F4_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix4F4_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix4F4_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix4F4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Matrix4F4.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Vector4F.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/mac-matrix4f4-ut.supp
)
