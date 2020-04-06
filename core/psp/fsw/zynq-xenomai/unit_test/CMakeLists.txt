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
 
include(${PROJECT_SOURCE_DIR}/osal/src/make/build-functions.cmake)

set(PSP_PLATFORM_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_exception.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_memory.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_memtab.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_ssr.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_start.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_support.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_timer.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_voltab.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_watchdog.c
    PARENT_SCOPE
)

set(PSP_UNIT_TEST_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/psp_testcase.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/psp_testrunner.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../unit_test/stubs.c
    ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/utassert.c
    ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/utlist.c
    ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/uttest.c
    ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/uttools.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_exception.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_memory.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_memtab.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_ssr.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_start.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_support.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_timer.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_voltab.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_psp_watchdog.c
    PARENT_SCOPE
)

set(PSP_UNIT_TEST_COUNT 49)

#target_include_directories(${PARSED_ARGS_TARGET} PUBLIC ${PROJECT_BINARY_DIR}/inc)
#target_include_directories(${PARSED_ARGS_TARGET} PUBLIC ${PARSED_ARGS_INCLUDES})
#target_include_directories(${PARSED_ARGS_TARGET} PUBLIC ${CFE_INC_DIRS})
#target_include_directories(${PARSED_ARGS_TARGET} PUBLIC ${OSAL_INC_DIRS})
#target_include_directories(${PARSED_ARGS_TARGET} PUBLIC ${PSP_INC_DIRS})

add_executable(psp-unit-test ${PSP_UNIT_TEST_SRC})
target_link_libraries(psp-unit-test -fprofile-arcs gcov ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(psp-unit-test PROPERTIES COMPILE_FLAGS "-g -O0 -Wformat=0 -Wno-int-to-pointer-cast -fprofile-arcs -ftest-coverage")

target_include_directories(psp-unit-test PUBLIC
    ${PROJECT_SOURCE_DIR}/tools/ut_assert/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${OSAL_INC_DIRS}
)

set(PSP_OSAL_UTASSERT_BSP_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/bsp_voltab.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bsp_ut.c
    PARENT_SCOPE
)

set(PSP_OSAL_UT_BSP_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/bsp_start.c
    PARENT_SCOPE
)


set(memcheck_command "valgrind --tool=memcheck --leak-check=full --show-reachable=yes --undef-value-errors=yes --num-callers=20 --track-origins=no --child-silent-after-fork=no --trace-children=no --xml=yes --xml-file=dynamic-analysis-%p.xml")
set(helgrind_command "valgrind --tool=helgrind --tool=helgrind --num-callers=20 --child-silent-after-fork=no --trace-children=no --xml=yes --xml-file=dynamic-analysis-%p.xml")
separate_arguments(memcheck_command)
separate_arguments(helgrind_command)

if(PSP_UNIT_TEST_WRAPPER)
    if(PSP_UNIT_TEST_COUNT)
        set(TEST_CASE 0)
        while(TEST_CASE LESS PSP_UNIT_TEST_COUNT)
            math(EXPR TEST_CASE "${TEST_CASE}+1")
            add_test(psp-unit-test-${TEST_CASE} ${PSP_UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ./psp-unit-test --test ${TEST_CASE})
            add_test(psp-unit-test-${TEST_CASE}-memcheck ${PSP_UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${memcheck_command} ./psp-unit-test --test ${TEST_CASE})
            add_test(psp-unit-test-${TEST_CASE}-helgrind ${PSP_UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${helgrind_command} ./psp-unit-test --test ${TEST_CASE})
        endwhile()
    else()
        add_test(psp-unit-test ${PSP_UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ./psp-unit-test})
        add_test(psp-unit-test-memcheck ${PSP_UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${memcheck_command} ./psp-unit-test)
        add_test(psp-unit-test-helgrind ${PSP_UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${helgrind_command} ./psp-unit-test)
    endif()
else()
    if(PSP_UNIT_TEST_COUNT)
	set(TEST_CASE 0)
	while(TEST_CASE LESS PSP_UNIT_TEST_COUNT)
	    math(EXPR TEST_CASE "${TEST_CASE}+1")
	    add_test(psp-unit-test-${TEST_CASE} ${CMAKE_CURRENT_BINARY_DIR}/psp-unit-test --test ${TEST_CASE})
	    add_test(psp-unit-test-${TEST_CASE}-memcheck ${memcheck_command} ${CMAKE_CURRENT_BINARY_DIR}/psp-unit-test --test ${TEST_CASE})
	    add_test(psp-unit-test-${TEST_CASE}-helgrind ${helgrind_command} ${CMAKE_CURRENT_BINARY_DIR}/psp-unit-test --test ${TEST_CASE})
	endwhile()
    else()
        add_test(psp-unit-test ${CMAKE_CURRENT_BINARY_DIR}/psp-unit-test)
	add_test(psp-unit-test-memcheck ${memcheck_command} ${CMAKE_CURRENT_BINARY_DIR}/psp-unit-test)
	add_test(psp-unit-test-helgrind ${helgrind_command} ${CMAKE_CURRENT_BINARY_DIR}/psp-unit-test)
    endif()
endif()
