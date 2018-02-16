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
 # 3. Neither the name Windhover Labs nor the names of its contributors 
 #    may be used to endorse or promote products derived from this software
 #    without specific prior written permission.
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

set(PX4LIB_PUBLIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc)

add_subdirectory(../src/ src)

add_airliner_app_def(px4lib
    FILE PX4LIB
    SOURCES
        ${PX4LIB_SOURCES}

    INCLUDES
        ${PX4LIB_INCLUDES}
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
   
    PUBLIC_INCLUDES
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/
)


add_airliner_app_unit_test(px4lib-vector3f-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector3F_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector3F_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector3F_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector3F_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector3F_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector3F.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector10F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector10F.hpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F3.hpp
        
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-vector3f-ut.supp
)


add_airliner_app_unit_test(px4lib-vector4f-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector4F_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector4F_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector4F_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector4F_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Vector4F_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector4F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector4F.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-vector4f-ut.supp
)


add_airliner_app_unit_test(px4lib-quaternion-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Quaternion_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Quaternion_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Quaternion_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Quaternion_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Quaternion_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Quaternion.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Quaternion.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector4F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector4F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector3F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix3F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector10F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector10F.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-quaternion-ut.supp
)


add_airliner_app_unit_test(px4lib-matrix3f3-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix3F3_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix3F3_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix3F3_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix3F3_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix3F3_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix3F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector3F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector10F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector10F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F3.hpp

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-matrix3f3-ut.supp
)


add_airliner_app_unit_test(px4lib-matrix4f4-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix4F4_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix4F4_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix4F4_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix4F4_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix4F4_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix4F4.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix4F4.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector4F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector4F.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-matrix4f4-ut.supp
)


add_airliner_app_unit_test(px4lib-matrix6f6-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix6F6_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix6F6_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix6F6_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix6F6_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix6F6_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F6.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F6.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector1F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector1F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector6F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector6F.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-matrix6f6-ut.supp
)



add_airliner_app_unit_test(px4lib-matrix1f10-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix1F10_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix1F10_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix1F10_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix1F10_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix1F10_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix3F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix3F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F6.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F6.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F6.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F6.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector1F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector1F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector3F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector6F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector6F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector10F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector10F.hpp

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-matrix1f10-ut.supp
)


add_airliner_app_unit_test(px4lib-matrix10f1-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix10F1_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix10F1_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix10F1_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix10F1_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix10F1_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix3F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix3F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F6.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F6.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F6.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F6.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector1F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector1F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector3F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector6F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector6F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector10F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector10F.hpp

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-matrix10f1-ut.supp
)

add_airliner_app_unit_test(px4lib-matrix1f1-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix1F1_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix1F1_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix1F1_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix1F1_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix1F1_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector1F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector1F.hpp
        
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-matrix1f1-ut.supp
)


add_airliner_app_unit_test(px4lib-matrix10f10-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix10F10_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix10F10_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix10F10_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix10F10_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix10F10_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix3F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix3F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F6.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F6.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F6.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F6.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector1F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector1F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector3F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector6F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector6F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector10F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector10F.hpp

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-matrix10f10-ut.supp
)



add_airliner_app_unit_test(px4lib-matrix6f10-ut
    UTASSERT
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix6F10_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix6F10_test.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix6F10_testrunner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix6F10_test_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/Matrix6F10_test_utils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector6F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector6F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector10F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector10F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix3F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix1F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix1F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix3F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix3F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F6.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F6.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix6F6.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix6F6.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F3.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F3.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F10.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F10.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Matrix10F1.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Matrix10F1.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector3F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector3F.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/math/Vector1F.cpp
        ${PX4LIB_PUBLIC_INCLUDE_DIR}/math/Vector1F.hpp

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/
        ${PX4LIB_PUBLIC_INCLUDE_DIR}
        
    VALGRIND_SUPPRESSION_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/px4lib-matrix6f10-ut.supp
)


set(PX4LIB_LIB_SOURCES ${PX4LIB_LIB_SOURCES} CACHE STRING "PX4LIB library source files")
