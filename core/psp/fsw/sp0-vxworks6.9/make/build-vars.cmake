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
 
# Collect PSP includes and source
set(PSP_INC_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/../inc
    ${CMAKE_CURRENT_LIST_DIR}/../../inc
    # BSP include paths, required by PSP
    #$ENV{WIND_HOME}/vxworks/bsp
    $ENV{WIND_HOME}/vxworks-6.9/target/3rdparty/aitech/sp0/
)

# Set libraries to link into the main executable
set(LIBS "")

set(CMAKE_C_FLAGS "")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_EXECUTABLE_LINK_C_FLAGS "")
set(CMAKE_C_COMPILE_OPTIONS_PIC "")
set(CMAKE_CXX_COMPILE_OPTIONS_PIC "")
set(CMAKE_SHARED_LIBRARY_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_CXX_FLAGS "")
set(CMAKE_SHARED_MODULE_C_FLAGS "")
set(CMAKE_SHARED_MODULE_CXX_FLAGS "")
set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "")
set(CMAKE_SHARED_MODULE_CREATE_C_FLAGS "")
set(CMAKE_SHARED_MODULE_CREATE_CXX_FLAGS "")


# Set compiler flags for apps and the main executable.
set(COMPILE_FLAGS "-D_VXWORKS_OS_ -D_PPC_ -D__PPC__  -g -te500v2 -mhard-float \
                   -fno-implicit-fp -mstrict-align -fno-builtin \
                   -fno-zero-initialized-in-bss  -Wall    -MD -MP -pedantic \
                   -DCPU=_VX_PPC85XX -DTOOL_FAMILY=gnu \
                   -DTOOL=e500v2gnu -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"\\\"$ENV{WIND_BASE}/target/lib/h/config/vsbConfig.h\\\"\" \
                   -DIP_PORT_VXWORKS=69 -fno-PIC \
                   -I$ENV{WIND_BASE}/target/h \
                   -I$ENV{WIND_BASE}/target/h/wrn/coreip")
set(LINK_FLAGS "-nostdlib -Wl,-X")

# the name of the target operating system
set(CMAKE_SYSTEM_NAME VxWorks)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER ccppc)
set(CMAKE_C_FLAGS "${COMPILE_FLAGS} -std=c99")
set(CMAKE_CXX_COMPILER c++ppc)
set(CMAKE_CXX_FLAGS "${COMPILE_FLAGS} -std=c++98")

set(INSTALL_DIR	      ${CMAKE_CURRENT_BINARY_DIR}/exe/cf/apps)
set(CFE_INSTALL_DIR   ${CMAKE_CURRENT_BINARY_DIR}/exe)

set(MEMCHECK_COMMAND "valgrind --tool=memcheck --leak-check=full --show-reachable=yes --undef-value-errors=yes --num-callers=20 --track-origins=yes --child-silent-after-fork=no --trace-children=no --xml=yes --xml-file=dynamic-analysis-%p.xml --gen-suppressions=all")
set(HELGRIND_COMMAND "valgrind --tool=helgrind --num-callers=20 --child-silent-after-fork=no --trace-children=no --xml=yes --xml-file=dynamic-analysis-%p.xml --gen-suppressions=all")
set(MASSIF_COMMAND "valgrind --tool=massif --heap=yes --stacks=yes --massif-out-file=massif-%p.out")
separate_arguments(MEMCHECK_COMMAND)
separate_arguments(HELGRIND_COMMAND)
separate_arguments(MASSIF_COMMAND)
set(MEMCHECK_COMMAND ${MEMCHECK_COMMAND} PARENT_SCOPE)
set(HELGRIND_COMMAND ${helgrind_command} PARENT_SCOPE)
set(MASSIF_COMMAND ${massif_command} PARENT_SCOPE)
set(INSTALL_DIR	      ${INSTALL_DIR} PARENT_SCOPE)

set(COMMANDER_WORKSPACE_PLUGINS_DIR ${CMAKE_CURRENT_BINARY_DIR}/commander/commander_workspace/plugins PARENT_SCOPE)


set(PSP_INC_DIRS ${PSP_INC_DIRS} PARENT_SCOPE)
set(LIBS ${LIBS} PARENT_SCOPE)
set(COMPILE_FLAGS ${COMPILE_FLAGS} PARENT_SCOPE)
set(CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME} PARENT_SCOPE)
set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER} PARENT_SCOPE)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} PARENT_SCOPE)
set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER} PARENT_SCOPE)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} PARENT_SCOPE)
set(CMAKE_EXECUTABLE_LINK_C_FLAGS ${CMAKE_EXECUTABLE_LINK_C_FLAGS} PARENT_SCOPE)
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS ${CMAKE_EXECUTABLE_LINK_C_FLAGS} PARENT_SCOPE)
set(CMAKE_C_COMPILE_OPTIONS_PIC ${CMAKE_C_COMPILE_OPTIONS_PIC} PARENT_SCOPE)
set(CMAKE_CXX_COMPILE_OPTIONS_PIC ${CMAKE_CXX_COMPILE_OPTIONS_PIC} PARENT_SCOPE)
set(CMAKE_SHARED_LIBRARY_C_FLAGS ${CMAKE_SHARED_LIBRARY_C_FLAGS} PARENT_SCOPE)
set(CMAKE_SHARED_LIBRARY_CXX_FLAGS ${CMAKE_SHARED_LIBRARY_CXX_FLAGS} PARENT_SCOPE)
set(CMAKE_SHARED_MODULE_C_FLAGS ${CMAKE_SHARED_MODULE_C_FLAGS} PARENT_SCOPE)
set(CMAKE_SHARED_MODULE_CXX_FLAGS ${CMAKE_SHARED_MODULE_CXX_FLAGS} PARENT_SCOPE)
set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS ${CMAKE_SHARED_MODULE_CXX_FLAGS} PARENT_SCOPE)
set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS ${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} PARENT_SCOPE)
set(CMAKE_SHARED_MODULE_CREATE_C_FLAGS ${CMAKE_SHARED_MODULE_CREATE_C_FLAGS} PARENT_SCOPE)
set(CMAKE_SHARED_MODULE_CREATE_CXX_FLAGS ${CMAKE_SHARED_MODULE_CREATE_CXX_FLAGS} PARENT_SCOPE)

set(PSP_UNIT_TEST_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../unit_test)

set(PSP_WB_UT_BSP_SRC
    ${PSP_UNIT_TEST_SRC_DIR}/bsp_start.c
    ${PSP_UNIT_TEST_SRC_DIR}/bsp_voltab.c 
)

set(PSP_BB_UT_BSP_SRC
    ${PSP_UNIT_TEST_SRC_DIR}/bsp_ut.c
    ${PSP_UNIT_TEST_SRC_DIR}/bsp_voltab.c 
)

set(PSP_OSAL_UTASSERT_BSP_SRC 
    ${PSP_UNIT_TEST_SRC_DIR}/bsp_voltab.c
    ${PSP_UNIT_TEST_SRC_DIR}/bsp_ut.c
)

set(MEMCHECK_COMMAND ${MEMCHECK_COMMAND} PARENT_SCOPE)
set(HELGRIND_COMMAND ${HELGRIND_COMMAND} PARENT_SCOPE)
set(MASSIF_COMMAND ${MASSIF_COMMAND} PARENT_SCOPE)

set(BUILD_CORE_FROM_SOURCE TRUE)



