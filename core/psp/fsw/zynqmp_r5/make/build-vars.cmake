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
    /home/mbenson/xsdk-workspace/firmware_r5_0_bsp/psu_cortexr5_0/include
    ${CMAKE_CURRENT_LIST_DIR}/../inc
    ${CMAKE_CURRENT_LIST_DIR}/../../inc
)

# Set libraries to link into the main executable
set(LIBS "-Wl,--start-group,-lxil,-lmetal,-lopen_amp,-lxilffs,-lfreertos,-lgcc,-lc,--end-group -Wl,--wrap=printf")

# Set compiler flags for apps and the main executable.
set(COMPILE_FLAGS "-DARMR5 -Wall -O0 -g3 -fmessage-length=0 -mcpu=cortex-r5 -MMD -MP -I/home/mbenson/xsdk-workspace/firmware_r5_0_bsp/psu_cortexr5_0/include" )
set(LINK_FLAGS "")

# the name of the target operating system
set(CMAKE_SYSTEM_NAME FreeRTOS)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER armr5-none-eabi-gcc)
#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-DARMR5 -Wall -O0 -g3 -fmessage-length=0 -mcpu=cortex-r5 -MMD -MP -I/home/mbenson/xsdk-workspace/firmware_r5_0_bsp/psu_cortexr5_0/include")
set(CMAKE_CXX_COMPILER armr5-none-eabi-g++)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-DARMR5 -Wall -O0 -g3 -fmessage-length=0 -mcpu=cortex-r5 -MMD -MP -I/home/mbenson/xsdk-workspace/firmware_r5_0_bsp/psu_cortexr5_0/include")

set(APP_LINK_FLAGS "-shared")

set(PLATFORM_AUX_SRC_CODE "/home/mbenson/git/airliner/core/psp/fsw/zynqmp_r5/unit_test/bsp_task_mem.c")

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

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-T -Wl,/home/mbenson/xsdk-workspace/firmware_r5_0/core/psp/src/lscript.ld -L/home/mbenson/xsdk-workspace/firmware_r5_0_bsp/psu_cortexr5_0/lib ")

set(COMMANDER_WORKSPACE_PLUGINS_DIR ${CMAKE_CURRENT_BINARY_DIR}/commander/commander_workspace/plugins PARENT_SCOPE)

set(CMAKE_LIBRARY_PATH /home/mbenson/xsdk-workspace/firmware_r5_0_bsp/psu_cortexr5_0/lib)
set(CMAKE_SYSTEM_LIBRARY_PATH /home/mbenson/xsdk-workspace/firmware_r5_0_bsp/psu_cortexr5_0/lib)

#set(CMAKE_EXECUTABLE_LINK_C_FLAGS "")
#set(CMAKE_EXECUTABLE_LINK_CXX_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
#set(CMAKE_C_COMPILE_OPTIONS_PIC "")
#set(CMAKE_CXX_COMPILE_OPTIONS_PIC "")
#set(CMAKE_SHARED_LIBRARY_C_FLAGS "")
#set(CMAKE_SHARED_LIBRARY_CXX_FLAGS "")
#set(CMAKE_SHARED_MODULE_C_FLAGS "")
#set(CMAKE_SHARED_MODULE_CXX_FLAGS "")
#set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "")
#set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "")
#set(CMAKE_SHARED_MODULE_CREATE_C_FLAGS "")
#set(CMAKE_SHARED_MODULE_CREATE_CXX_FLAGS "")

set(PSP_INC_DIRS ${PSP_INC_DIRS} PARENT_SCOPE)
set(LIBS ${LIBS} PARENT_SCOPE)
set(COMPILE_FLAGS ${COMPILE_FLAGS} PARENT_SCOPE)
set(LINK_FLAGS ${LINK_FLAGS} PARENT_SCOPE)
set(CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME} PARENT_SCOPE)
set(CMAKE_C_COMPILER ${CMAKE_C_COMPILER} PARENT_SCOPE)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} PARENT_SCOPE)
set(CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER} PARENT_SCOPE)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} PARENT_SCOPE)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} PARENT_SCOPE)
set(CMAKE_SYSTEM_LIBRARY_PATH ${CMAKE_SYSTEM_LIBRARY_PATH} PARENT_SCOPE)
set(CMAKE_EXECUTABLE_LINK_C_FLAGS ${CMAKE_EXECUTABLE_LINK_C_FLAGS} PARENT_SCOPE)
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS ${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} PARENT_SCOPE)
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS ${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} PARENT_SCOPE)
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
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} PARENT_SCOPE)
set(APP_LINK_FLAGS ${APP_LINK_FLAGS} PARENT_SCOPE)
set(PLATFORM_AUX_SRC_CODE ${PLATFORM_AUX_SRC_CODE} PARENT_SCOPE)

set(PSP_UNIT_TEST_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../unit_test)

set(PSP_OSAL_UT_BSP_SRC ${PSP_UNIT_TEST_SRC_DIR}/bsp_start.c)

set(PSP_OSAL_UTASSERT_BSP_SRC 
    ${PSP_UNIT_TEST_SRC_DIR}/bsp_voltab.c
    ${PSP_UNIT_TEST_SRC_DIR}/bsp_ut.c
)

set(MEMCHECK_COMMAND ${MEMCHECK_COMMAND} PARENT_SCOPE)
set(HELGRIND_COMMAND ${HELGRIND_COMMAND} PARENT_SCOPE)
set(MASSIF_COMMAND ${MASSIF_COMMAND} PARENT_SCOPE)

set(BUILD_CORE_FROM_SOURCE TRUE)
