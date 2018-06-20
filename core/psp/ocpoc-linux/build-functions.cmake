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
 
set(PSP_UNIT_TEST_WRAPPER "")

#build_airliner_cfe(
#    PSP    ocpoc-linux
#    OSAL   posix
#    CONFIG
#        ${CMAKE_CURRENT_SOURCE_DIR}/inc
#        ${CMAKE_CURRENT_SOURCE_DIR}/../shared/inc
#    FILESYS
#        /cf/apps
#        /cf/download
#        /cf/log
#        /cf/upload
#        /ram
#    STARTUP_SCRIPT
#        ${CMAKE_CURRENT_SOURCE_DIR}/cfe_es_startup.scr
#)
function(psp_build_airliner_cfe)
    # Define the function arguments.
    cmake_parse_arguments(PARSED_ARGS "" "PREFIX;OSAL;STARTUP_SCRIPT;UNIT_TEST_WRAPPER;CONFIG_SOURCES" "FILESYS" ${ARGN})

    set(PSP_UNIT_TEST_WRAPPER target/${PARSED_ARGS_UNIT_TEST_WRAPPER})
    
    # Create all the target directories the caller requested.
    foreach(dir ${PARSED_ARGS_FILESYS})
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/exe/${dir})
    endforeach()
    
    # Find the Nano Protobuf utility to use later.
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/tools/nanopb/extra)
    find_package(Nanopb REQUIRED)

    # Set source files
    add_subdirectory(${CFE_PSP_DIR}/make psp)
    
    if(NOT TARGET rsm)   
        add_custom_target(rsm)
    endif()
    if(NOT ${PARSED_ARGS_PREFIX})
        add_custom_target(${PARSED_ARGS_PREFIX}rsm)
    endif()
    
    # Copy the startup script into the default location.
    file(COPY ${PARSED_ARGS_STARTUP_SCRIPT} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/exe/cf/apps)

    # Set what we're going to call the executable file.
    set(CFE_EXEC_FILE core-bin)

    # Where to put applications
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR})

    # Where to put tables
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${INSTALL_DIR})

    # Parse the OSAL CMake files that will specify the various source files.
    add_subdirectory(${PARSED_ARGS_OSAL} osal)

    # Now build CFE using the various source files that just parsed.
    add_executable(${PARSED_ARGS_PREFIX}${CFE_EXEC_FILE} ${CFE_SRC} ${OSAL_SRC} ${PSP_PLATFORM_SRC} ${PSP_SHARED_SRC})
    set_target_properties(${PARSED_ARGS_PREFIX}${CFE_EXEC_FILE} PROPERTIES OUTPUT_NAME ${CFE_EXEC_FILE})
    
    # Add the OSAL include paths, if any. 
    target_include_directories(${PARSED_ARGS_PREFIX}${CFE_EXEC_FILE} PUBLIC ${OSAL_INCS})

    # Make sure we enable exports, to prevent the compiler from optimizing them out.  This needs to be done so the
    # applications can call all the CFE functions.  Otherwise, the compiler will just remove most of the functions
    # because they aren't being used by CFE.
    set_target_properties(${PARSED_ARGS_PREFIX}${CFE_EXEC_FILE} PROPERTIES ENABLE_EXPORTS TRUE)

    # Link in the various libraries specified by the PSP
    target_link_libraries(${PARSED_ARGS_PREFIX}${CFE_EXEC_FILE} ${LIBS})

    # Add in the various flags also supplied by the PSP.
    set_target_properties(${PARSED_ARGS_PREFIX}${CFE_EXEC_FILE} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})
    if(NOT LINK_FLAGS STREQUAL "")
        set_target_properties(${PARSED_ARGS_PREFIX}${CFE_EXEC_FILE} PROPERTIES LINK_FLAGS ${LINK_FLAGS})
    endif()

    # Specify where the files are going to, defined at the top of this file.
    set_target_properties(${PARSED_ARGS_PREFIX}${CFE_EXEC_FILE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CFE_INSTALL_DIR})

    # Generate documentation
    #add_subdirectory($ENV{CFE_DIR}/docs docs)
    
    ## Generate documentation
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        string (REPLACE ";" " " OSAL_SRC_FILES "${OSAL_SRC}")
        string (REPLACE ";" " " CONFIG_SOURCES "${PARSED_ARGS_CONFIG_SOURCES}")

        if(NOT {PARSED_ARGS_PREFIX}docs)        
            add_custom_target(${PARSED_ARGS_PREFIX}docs)
        endif()
        
        set(CFS_DOCS_HTML_DIR ${CMAKE_BINARY_DIR}/docs/html)
        set(CFS_DOCS_LATEX_DIR ${CMAKE_BINARY_DIR}/docs/latex)      
        configure_file(${PROJECT_SOURCE_DIR}/cfe/docs/user_doxy.in ${CMAKE_CURRENT_BINARY_DIR}/user_doxy @ONLY)
        configure_file(${PROJECT_SOURCE_DIR}/cfe/docs/detail_doxy.in ${CMAKE_CURRENT_BINARY_DIR}/detail_doxy @ONLY)
        add_custom_target(${PARSED_ARGS_PREFIX}cfe-docs
            COMMAND mkdir -p ${CFS_DOCS_HTML_DIR}/detailed_design/cfe/
            COMMAND mkdir -p ${CFS_DOCS_HTML_DIR}/users_guide/cfe/
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/detail_doxy
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/user_doxy
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
        )
        add_dependencies(${PARSED_ARGS_PREFIX}docs ${PARSED_ARGS_PREFIX}cfe-docs)
    endif(DOXYGEN_FOUND)
    
    if(NOT RSM_EXEC-NOTFOUND) 
        foreach(FILE ${CFE_SRC})
            list(APPEND SRC_TEXT ${FILE})
        endforeach()  
        foreach(FILE ${OSAL_SRC})
            list(APPEND SRC_TEXT ${FILE})
        endforeach()
        foreach(FILE ${PSP_PLATFORM_SRC})
            list(APPEND SRC_TEXT ${FILE})
        endforeach()
        foreach(FILE ${PSP_SHARED_SRC})
            list(APPEND SRC_TEXT ${FILE})
        endforeach()
        add_custom_target(${PARSED_ARGS_PREFIX}cfe-rsm
            COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/rsm/cfe/            
            COMMAND ${CMAKE_COMMAND} 
                -DRSM_EXEC:STRING='${RSM_EXEC}'
                -DRSM_CONFIG:STRING='${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/make/rsm/rsm.cfg'
                -DSOURCES:STRING='${SRC_TEXT}'
                -DOUTPUT_FILE:STRING='${CMAKE_CURRENT_BINARY_DIR}/rsm/cfe/index.html'
                -P ${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/make/run-rsm.cmake
        )
        add_dependencies(${PARSED_ARGS_PREFIX}rsm ${PARSED_ARGS_PREFIX}cfe-rsm)
    endif()  
    
    #set(MEMCHECK_COMMAND ${MEMCHECK_COMMAND} PARENT_SCOPE)
    set(HELGRIND_COMMAND ${HELGRIND_COMMAND} PARENT_SCOPE)
    set(MASSIF_COMMAND ${MASSIF_COMMAND} PARENT_SCOPE)

endfunction(psp_build_airliner_cfe)


function(psp_add_test)
    set(TEST_NAME ${ARGV0})
    # Define the function arguments.
    cmake_parse_arguments(PARSED_ARGS "NO_MEMCHECK;NO_HELGRIND;NO_MASSIF" "VALGRIND_SUPPRESSION_FILE" "SOURCES;LIBS;INCLUDES;WRAPPERS" ${ARGN})
    
    get_property(AIRLINER_BUILD_PREFIX GLOBAL PROPERTY AIRLINER_BUILD_PREFIX_PROPERTY)
    
    foreach(dir ${PARSED_ARGS_FILESYS})
        file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${dir})
    endforeach()

    add_executable(${AIRLINER_BUILD_PREFIX}${TEST_NAME}
        ${PARSED_ARGS_SOURCES}
    )

    add_executable(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov
        ${PARSED_ARGS_SOURCES}
    )
    
    foreach(FUNCTION ${PARSED_ARGS_WRAPPERS})
        set_property(TARGET ${AIRLINER_BUILD_PREFIX}${TEST_NAME}
            APPEND_STRING
            PROPERTY
            LINK_FLAGS
            "-Wl,--wrap=${FUNCTION} "
        )
        set_property(TARGET ${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov
            APPEND_STRING
            PROPERTY
            LINK_FLAGS
            "-Wl,--wrap=${FUNCTION} "
        )
    endforeach()
 
    target_compile_definitions(${AIRLINER_BUILD_PREFIX}${TEST_NAME}
        PUBLIC
        UT_VERBOSE
    )
    target_compile_definitions(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov
        PUBLIC
        UT_VERBOSE
    )
    
    target_include_directories(${AIRLINER_BUILD_PREFIX}${TEST_NAME} PUBLIC ${PARSED_ARGS_INCLUDES})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov PUBLIC ${PARSED_ARGS_INCLUDES})

    target_link_libraries(${AIRLINER_BUILD_PREFIX}${TEST_NAME} -ldl -lrt ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov -fprofile-arcs gcov -ldl -lrt ${CMAKE_THREAD_LIBS_INIT})

    set_target_properties(${AIRLINER_BUILD_PREFIX}${TEST_NAME} PROPERTIES COMPILE_FLAGS "-g -O0 -Wformat=0 -Wno-int-to-pointer-cast")
    set_target_properties(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov PROPERTIES COMPILE_FLAGS "-g -O0 -Wformat=0 -Wno-int-to-pointer-cast -fprofile-arcs -ftest-coverage")

    if(UNIT_TEST_WRAPPER)
        add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME} ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov)
        
        if(EXISTS ${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
            set(MEMCHECK_COMMAND ${MEMCHECK_COMMAND} --suppressions=${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
            set(HELGRIND_COMMAND ${HELGRIND_COMMAND} --suppressions=${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
        endif()
        
        #if(NOT PARSED_ARGS_NO_MEMCHECK)
        #    add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-memcheck ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${MEMCHECK_COMMAND} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        #endif()
    
        #if(NOT PARSED_ARGS_NO_HELGRIND)
        #    add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-helgrind ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${HELGRIND_COMMAND} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        #endif()
    
        #if(NOT PARSED_ARGS_NO_MASSIF)
        #    add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-massif ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${MASSIF_COMMAND} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        #endif()
    else()
        add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME} ${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov ${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov)
        
        if(EXISTS ${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
            set(MEMCHECK_COMMAND ${MEMCHECK_COMMAND} --suppressions=${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
            set(HELGRIND_COMMAND ${HELGRIND_COMMAND} --suppressions=${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
        endif()
        
        #if(NOT PARSED_ARGS_NO_MEMCHECK)
        #    add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-memcheck ${MEMCHECK_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        #endif()
        
        #if(NOT PARSED_ARGS_NO_HELGRIND)
        #    add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-helgrind ${HELGRIND_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        #endif()
    
        #if(NOT PARSED_ARGS_NO_MASSIF)
        #    add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-massif ${MASSIF_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        #endif()
    endif(UNIT_TEST_WRAPPER)
endfunction(psp_add_test)


#add_airliner_app(
#    DEFINITION
#        ${PROJECT_SOURCE_DIR}/apps/cfs_lib
#    CONFIG
#        ${CMAKE_CURRENT_SOURCE_DIR}/apps/cfs_lib
#)
# This function doesn't actually add the application.  It calls the CMakeLists.txt in the application source directory,
# which actually adds the application.
function(psp_add_airliner_app)
    # Define the application name.
    set(PARSED_ARGS_APP_NAME ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS "" "DEFINITION" "CONFIG;CONFIG_SOURCES" ${ARGN})

    # Call the CMake file that actually defines the application.
    add_subdirectory(${PARSED_ARGS_DEFINITION} ${CMAKE_CURRENT_BINARY_DIR}/apps/${PARSED_ARGS_APP_NAME})

    # Most applications also include a CMakeLists.txt file that will define the application tailoring or configuration,
    # but not all.  If a configuration is supplied, call it.
    if(NOT ${PARSED_ARGS_CONFIG} STREQUAL "")
        add_subdirectory(${PARSED_ARGS_CONFIG} ${CMAKE_CURRENT_BINARY_DIR}/config/apps/${PARSED_ARGS_APP_NAME})
    endif()

    get_property(AIRLINER_BUILD_PREFIX GLOBAL PROPERTY AIRLINER_BUILD_PREFIX_PROPERTY)
    
    target_sources(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME} PUBLIC ${PARSED_ARGS_CONFIG_SOURCES})
    
    get_property(USER_DOCS_INPUT TARGET ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME} PROPERTY USER_DOCS_INPUT)
    get_property(DESIGN_DOCS_INPUT TARGET ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME} PROPERTY DESIGN_DOCS_INPUT)  
    get_property(APP_DEFINITION_DIR TARGET ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME} PROPERTY APP_DEFINITION_DIR)   
    get_property(DEFINITION_SOURCES_LIST TARGET ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME} PROPERTY APP_DEFINITION_SRC) 
    get_property(PROTOBUF_MSGS TARGET ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME} PROPERTY PROTOBUF_MSGS) 
    
    string (REPLACE ";" " " CONFIG_SOURCES "${PARSED_ARGS_CONFIG_SOURCES}")
    string (REPLACE ";" " " DEFINITION_SOURCES "${DEFINITION_SOURCES_LIST}")
        
    ## Generate documentation
    find_package(Doxygen)
    if(DOXYGEN_FOUND) 
        if(USER_DOCS_INPUT)
            if(NOT TARGET ${AIRLINER_BUILD_PREFIX}docs)
                add_custom_target(${AIRLINER_BUILD_PREFIX}docs)
            endif()
            add_custom_target(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-docs)
            add_dependencies(${AIRLINER_BUILD_PREFIX}docs ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-docs)
            add_dependencies(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-docs ${AIRLINER_BUILD_PREFIX}cfe-docs)
            configure_file(${USER_DOCS_INPUT} ${CMAKE_CURRENT_BINARY_DIR}/target/config/apps/${PARSED_ARGS_APP_NAME}/user_doxy @ONLY)
            add_custom_target(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-user-docs
                COMMAND mkdir -p ${CFS_DOCS_HTML_DIR}/users_guide/apps/${PARSED_ARGS_APP_NAME}/
                COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/target/config/apps/${PARSED_ARGS_APP_NAME}/user_doxy
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/target/config/apps/${PARSED_ARGS_APP_NAME}
            )
            add_dependencies(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-user-docs ${AIRLINER_BUILD_PREFIX}cfe-docs)
            add_dependencies(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-docs ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-user-docs)
        endif(USER_DOCS_INPUT)
        if(DESIGN_DOCS_INPUT)
            if(NOT TARGET ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-docs)
                add_custom_target(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-docs)
                add_dependencies(${AIRLINER_BUILD_PREFIX}docs ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-docs)
            endif()
            configure_file(${DESIGN_DOCS_INPUT} ${CMAKE_CURRENT_BINARY_DIR}/target/config/apps/${PARSED_ARGS_APP_NAME}/detail_doxy @ONLY)
            add_custom_target(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-design-docs
                COMMAND mkdir -p ${CFS_DOCS_HTML_DIR}/detailed_design/apps/${PARSED_ARGS_APP_NAME}/
                COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/target/config/apps/${PARSED_ARGS_APP_NAME}/detail_doxy
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/target/config/apps/${PARSED_ARGS_APP_NAME}
            )
            add_dependencies(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-design-docs ${AIRLINER_BUILD_PREFIX}cfe-docs)
            add_dependencies(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-docs ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-design-docs)
        endif(DESIGN_DOCS_INPUT)
    endif(DOXYGEN_FOUND)
    
    if(NOT TARGET rsm)
        add_custom_target(rsm)
    endif()
    
    if(NOT RSM_EXEC-NOTFOUND) 
        get_directory_property(CURRENT_INCDIRS INCLUDE_DIRECTORIES)
        foreach(FILE ${PARSED_ARGS_CONFIG_SOURCES})
            list(APPEND SOURCE_LIST ${FILE})
        endforeach()
        foreach(FILE ${DEFINITION_SOURCES_LIST})
            list(APPEND SOURCE_LIST ${FILE})
        endforeach()

        add_custom_target(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-rsm
            COMMAND mkdir -p '${CMAKE_CURRENT_BINARY_DIR}/rsm/apps/${PARSED_ARGS_APP_NAME}'
            COMMAND ${CMAKE_COMMAND} 
                -DRSM_EXEC:STRING='${RSM_EXEC}'
                -DRSM_CONFIG:STRING='${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/make/rsm/rsm.cfg'
                -DSOURCES:STRING='${SOURCE_LIST}'
                -DOUTPUT_FILE:STRING='${CMAKE_CURRENT_BINARY_DIR}/rsm/apps/${PARSED_ARGS_APP_NAME}/index.html'
                -P ${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/make/run-rsm.cmake
        )
        add_dependencies(rsm ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_APP_NAME}-rsm)
    endif()
    
endfunction(psp_add_airliner_app)



#add_airliner_app_def(sch
#    FILE SCH
#    SOURCES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_api.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_app.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/sch_cmds.c
#
#    INCLUDES
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/
#        ${CMAKE_CURRENT_SOURCE_DIR}/../public_inc/
#   
#    UNIT_TEST_SOURCES
#
#    UNIT_TEST_INCLUDES
#)
function(psp_add_airliner_app_def)
    set(PARSED_ARGS_TARGET ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS ""  "PREFIX;FILE" "SOURCES;LIBS;INCLUDES;PUBLIC_INCLUDES;USER_DOCS;DESIGN_DOCS;PROTOBUF_DEFS;PROTOBUF_MSGS_DIR" ${ARGN})
    
    get_property(PUBLIC_APP_INCLUDES GLOBAL PROPERTY PUBLIC_APP_INCLUDES_PROPERTY)
    set(PUBLIC_APP_INCLUDES "${PUBLIC_APP_INCLUDES} ${PARSED_ARGS_PUBLIC_INCLUDES}")
    set_property(GLOBAL PROPERTY PUBLIC_APP_INCLUDES_PROPERTY ${PUBLIC_APP_INCLUDES})

    get_property(AIRLINER_BUILD_PREFIX GLOBAL PROPERTY AIRLINER_BUILD_PREFIX_PROPERTY)
    separate_arguments(PUBLIC_APP_INCLUDES)

    add_library(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} MODULE ${PARSED_ARGS_SOURCES})
    set_target_properties(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${PARSED_ARGS_INCLUDES})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${PUBLIC_APP_INCLUDES})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${CFE_INC_DIRS})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${OSAL_INC_DIRS})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${PSP_INC_DIRS})

    set_target_properties(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PROPERTIES PREFIX "")
    if(NOT ${PARSED_ARGS_FILE} EQUAL "")
        set_target_properties(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PROPERTIES OUTPUT_NAME ${PARSED_ARGS_FILE})
    endif()

    target_link_libraries(${PARSED_ARGS_TARGET} m)
    
    if(PARSED_ARGS_SOURCES)
        set_target_properties(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PROPERTIES APP_DEFINITION_SRC "${PARSED_ARGS_SOURCES}")
    endif()
    
    if(NOT ${PARSED_ARGS_USER_DOCS} EQUAL "")
        set_target_properties(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PROPERTIES USER_DOCS_INPUT "${PARSED_ARGS_USER_DOCS}")
    endif()
    
    if(NOT ${PARSED_ARGS_DESIGN_DOCS} EQUAL "")
        set_target_properties(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PROPERTIES DESIGN_DOCS_INPUT "${PARSED_ARGS_DESIGN_DOCS}")
    endif()
    
    set_target_properties(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PROPERTIES APP_DEFINITION_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
       
    if(PARSED_ARGS_PROTOBUF_DEFS)
        set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)

        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/tools/nanopb/extra")
        find_package(Nanopb REQUIRED)
        include_directories(${NANOPB_INCLUDE_DIRS})
        file(MAKE_DIRECTORY ${PARSED_ARGS_PROTOBUF_MSGS_DIR})
        nanopb_generate_cpp(PROTO_SRCS PROTO_HDRS ${PARSED_ARGS_PROTOBUF_MSGS_DIR} ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} ${PARSED_ARGS_PROTOBUF_DEFS})
    endif()
endfunction(psp_add_airliner_app_def)



function(psp_add_airliner_app_unit_test)
    set(PARSED_ARGS_TARGET ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS "UTF;UTASSERT;NO_MEMCHECK;NO_HELGRIND;NO_MASSIF;NANOPB" "FILE;UTF_OUTPUT_FILE;UTF_BLESSED_FILE;VALGRIND_SUPPRESSION_FILE" "SOURCES;LIBS;INCLUDES;WRAPPERS;" ${ARGN})
    
    get_property(AIRLINER_BUILD_PREFIX GLOBAL PROPERTY AIRLINER_BUILD_PREFIX_PROPERTY)
    
    add_executable(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} ${PARSED_ARGS_SOURCES})
    add_executable(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov ${PARSED_ARGS_SOURCES})
    
    target_link_libraries(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} -lm ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov -fprofile-arcs gcov -lm ${CMAKE_THREAD_LIBS_INIT})
    
    set_target_properties(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PROPERTIES COMPILE_FLAGS "-g -O0 -Wformat=0 -Wno-int-to-pointer-cast")
    set_target_properties(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PROPERTIES COMPILE_FLAGS "-g -O0 -Wformat=0 -Wno-int-to-pointer-cast -fprofile-arcs -ftest-coverage")
    
    if(PARSED_ARGS_UTASSERT)
        set(UTASSERT_SRC
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/utassert.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_es_hooks.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_es_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_evs_hooks.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_evs_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_fs_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_eeprom_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_memrange_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_memutils_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_ram_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_timer_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_psp_watchdog_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_sb_hooks.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_sb_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_tbl_hooks.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_tbl_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_time_hooks.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_cfe_time_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/utlist.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_osapi_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/ut_osfileapi_stubs.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/uttest.c
            ${PROJECT_SOURCE_DIR}/tools/ut_assert/src/uttools.c)
        
        target_sources(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${UTASSERT_SRC})
        target_sources(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${UTASSERT_SRC})
        
        target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/tools/ut_assert/inc/)
        target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${PROJECT_SOURCE_DIR}/tools/ut_assert/inc/)
    elseif(PARSED_ARGS_UTF)
        set(UTF_SRC
            ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_api.c
            ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_es_cds.c
            ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_esmempool.c
            ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_evs.c
            ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_cfe_psp_eeprom.c
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
            ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osfilesys.c
            ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_osloader.c
            ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_ostimer.c
            ${PROJECT_SOURCE_DIR}/tools/utf/src/utf_sim.c
            )
            
        target_sources(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${UTF_SRC})
        target_sources(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${UTF_SRC})
        
        target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/tools/utf/inc/)
        target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${PROJECT_SOURCE_DIR}/tools/utf/inc/)
    endif()

	if(PARSED_ARGS_NANOPB)
		set(NANOPB_SRC 
		    ${PROJECT_SOURCE_DIR}/tools/nanopb/pb.h
		    ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_common.c
			${PROJECT_SOURCE_DIR}/tools/nanopb/pb_common.h
		    ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_decode.c
		    ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_decode.h
		    ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_encode.c
		    ${PROJECT_SOURCE_DIR}/tools/nanopb/pb_encode.h
		)
			
                target_sources(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${NANOPB_SRC})
                target_sources(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${NANOPB_SRC})

		target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/tools/nanopb/)
		target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${PROJECT_SOURCE_DIR}/tools/nanopb/)
	endif()
	
	if(EXISTS ${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
            set(MEMCHECK_COMMAND ${MEMCHECK_COMMAND} --suppressions=${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
            set(HELGRIND_COMMAND ${HELGRIND_COMMAND} --suppressions=${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
	endif()
    
    get_property(PUBLIC_APP_INCLUDES GLOBAL PROPERTY PUBLIC_APP_INCLUDES_PROPERTY)
    separate_arguments(PUBLIC_APP_INCLUDES)
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${PUBLIC_APP_INCLUDES})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${PUBLIC_APP_INCLUDES})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} BEFORE PUBLIC ${PARSED_ARGS_INCLUDES})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov BEFORE PUBLIC ${PARSED_ARGS_INCLUDES})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${CFE_INC_DIRS})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${CFE_INC_DIRS})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${OSAL_INC_DIRS})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${OSAL_INC_DIRS})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${PSP_INC_DIRS})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${PSP_INC_DIRS})
    
    foreach(FUNCTION ${PARSED_ARGS_WRAPPERS})
        set_property(TARGET ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}
            APPEND_STRING
            PROPERTY
            LINK_FLAGS
            "-Wl,--wrap=${FUNCTION} "
        )
        set_property(TARGET ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov
            APPEND_STRING
            PROPERTY
            LINK_FLAGS
            "-Wl,--wrap=${FUNCTION} "
        )
    endforeach()
    
    if(NOT ${PARSED_ARGS_UTF_OUTPUT_FILE} EQUAL "")
        add_test(NAME ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} COMMAND ${CMAKE_COMMAND} 
            -DTEST_EXEC:STRING=${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}
            -DTEST_ARGS:STRING=
            -DUTF_BLESSED_FILE:STRING=${PARSED_ARGS_UTF_BLESSED_FILE}
            -DUTF_OUTPUT_FILE:STRING=${PARSED_ARGS_UTF_OUTPUT_FILE}
            -P ${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/make/utf_run_and_check.cmake)
            
        add_test(NAME ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov COMMAND ${CMAKE_COMMAND} 
            -DTEST_EXEC:STRING=${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov
            -DTEST_ARGS:STRING=
            -DUTF_BLESSED_FILE:STRING=${PARSED_ARGS_UTF_BLESSED_FILE}
            -DUTF_OUTPUT_FILE:STRING=${PARSED_ARGS_UTF_OUTPUT_FILE}
            -P ${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/make/utf_run_and_check.cmake)
            
        if(NOT PARSED_ARGS_NO_MEMCHECK)
            add_test(NAME ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-memcheck COMMAND ${CMAKE_COMMAND} 
                -DTEST_EXEC:STRING=${MEMCHECK_COMMAND}
                -DTEST_ARGS:STRING=${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}
                -DUTF_BLESSED_FILE:STRING=${PARSED_ARGS_UTF_BLESSED_FILE}
                -DUTF_OUTPUT_FILE:STRING=${PARSED_ARGS_UTF_OUTPUT_FILE}
                -P ${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/make/utf_run_and_check.cmake)
        endif()
        
        if(NOT PARSED_ARGS_NO_HELGRIND)
            add_test(NAME ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-helgrind COMMAND ${CMAKE_COMMAND} 
                -DTEST_EXEC:STRING=${HELGRIND_COMMAND}
                -DTEST_ARGS:STRING=${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}
                -DUTF_BLESSED_FILE:STRING=${PARSED_ARGS_UTF_BLESSED_FILE}
                -DUTF_OUTPUT_FILE:STRING=${PARSED_ARGS_UTF_OUTPUT_FILE}
                -P ${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/make/utf_run_and_check.cmake)
        endif()
            
        if(NOT PARSED_ARGS_NO_MASSIF)
            add_test(NAME ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-massif COMMAND ${CMAKE_COMMAND} 
                -DTEST_EXEC:STRING=${MASSIF_COMMAND}
                -DTEST_ARGS:STRING=${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}
                -DUTF_BLESSED_FILE:STRING=${PARSED_ARGS_UTF_BLESSED_FILE}
                -DUTF_OUTPUT_FILE:STRING=${PARSED_ARGS_UTF_OUTPUT_FILE}
                -P ${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/make/utf_run_and_check.cmake)
        endif()
    else()
        if(UNIT_TEST_WRAPPER)  
            add_test(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ./${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET})
            add_test(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ./${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov)

            #if(NOT PARSED_ARGS_NO_MEMCHECK)
            #    add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-memcheck ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${MEMCHECK_COMMAND} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
            #endif()
            
            #if(NOT PARSED_ARGS_NO_HELGRIND)
            #    add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-helgrind ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${HELGRIND_COMMAND} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
            #endif()
            
            #if(NOT PARSED_ARGS_NO_MASSIF)
            #    add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-massif ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${MASSIF_COMMAND} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
            #endif()
        else() 
            add_test(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET})
            add_test(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov ${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov)

            #if(NOT PARSED_ARGS_NO_MEMCHECK)
            #    add_test(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-memcheck ${MEMCHECK_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET})
            #endif()

            #if(NOT PARSED_ARGS_NO_HELGRIND)
            #    add_test(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-helgrind ${HELGRIND_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET})
            #endif()

            #if(NOT PARSED_ARGS_NO_MASSIF)
            #    add_test(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-massif ${MASSIF_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET})
            #endif()
        endif(UNIT_TEST_WRAPPER)
    endif()
endfunction(psp_add_airliner_app_unit_test)



function(set_global_airliner_includes)
    include_directories(${CFE_INC_DIRS})
    include_directories(${OSAL_INC_DIRS})
    include_directories(${PSP_INC_DIRS})
    include_directories(${PARSED_ARGS_CONFIG})
endfunction(set_global_airliner_includes)


function(psp_add_airliner_cfe_unit_test)
    set(TEST_NAME ${ARGV0}) 
    
    get_property(AIRLINER_BUILD_PREFIX GLOBAL PROPERTY AIRLINER_BUILD_PREFIX_PROPERTY)

    add_executable(${AIRLINER_BUILD_PREFIX}${TEST_NAME}
        ${PARSED_ARGS_SOURCES}
        ${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/unit_test/bsp_ut.c
    )

    add_executable(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov
        ${PARSED_ARGS_SOURCES}
        ${PROJECT_SOURCE_DIR}/psp/fsw/ocpoc-linux/unit_test/bsp_ut.c
    )

    target_include_directories(${AIRLINER_BUILD_PREFIX}${TEST_NAME} PUBLIC ${PARSED_ARGS_INCLUDES})
    target_include_directories(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov PUBLIC ${PARSED_ARGS_INCLUDES})

    target_link_libraries(${AIRLINER_BUILD_PREFIX}${TEST_NAME} -ldl -lrt ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov -fprofile-arcs gcov -ldl -lrt ${CMAKE_THREAD_LIBS_INIT})

    set_target_properties(${AIRLINER_BUILD_PREFIX}${TEST_NAME} PROPERTIES COMPILE_FLAGS "-g -O0 -Wformat=0 -Wno-int-to-pointer-cast")
    set_target_properties(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov PROPERTIES COMPILE_FLAGS "-g -O0 -Wformat=0 -Wno-int-to-pointer-cast -fprofile-arcs -ftest-coverage")

    if(EXISTS ${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
        set(MEMCHECK_COMMAND ${MEMCHECK_COMMAND} --suppressions=${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
        set(HELGRIND_COMMAND ${HELGRIND_COMMAND} --suppressions=${PARSED_ARGS_VALGRIND_SUPPRESSION_FILE})
    endif()
    
    if(UNIT_TEST_WRAPPER)
        add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME} ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov)
        #add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-memcheck ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${MEMCHECK_COMMAND} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        #add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-helgrind ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${HELGRIND_COMMAND} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        #add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-massif ${UNIT_TEST_WRAPPER} ${CMAKE_CURRENT_BINARY_DIR} ${MASSIF_COMMAND} ./${AIRLINER_BUILD_PREFIX}${TEST_NAME})
    else()
        add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME} ${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov ${AIRLINER_BUILD_PREFIX}${TEST_NAME}-gcov)
        #add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-memcheck ${MEMCHECK_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        #add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-helgrind ${HELGRIND_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${TEST_NAME})
        #add_test(${AIRLINER_BUILD_PREFIX}${TEST_NAME}-massif ${MASSIF_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/${AIRLINER_BUILD_PREFIX}${TEST_NAME})
    endif(UNIT_TEST_WRAPPER)
endfunction(psp_add_airliner_cfe_unit_test)


function(JOIN VALUES GLUE OUTPUT)
    string (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
    string (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
    set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()



##################################################################
#
# FUNCTION: get_current_cflags
#
# Convert the input string, which is a simple text string of compiler flags such
# as CMAKE_C_FLAGS or CMAKE_CXX_FLAGS, and convert it to a list of individual options
#
# In addition, the "-I" options from include_directories() and -D options from
# add_definitions() will be added to the output list.  The contents of these will be
# obtained via the properities of the current source directory.
#
function(psp_get_app_cflags APP_NAME OUTPUT_LIST INPUT_FLAGS)

    # Start by converting the supplied string to a list
    set(FLAGLIST)
    foreach (FLGSTR ${INPUT_FLAGS} ${ARGN})
        string(REGEX REPLACE " +" ";" TEMPFLG ${FLGSTR})
        list(APPEND FLAGLIST ${TEMPFLG})
    endforeach (FLGSTR ${INPUT_FLAGS} ${ARGN})

    # Append any compile definitions from the directory properties
    get_directory_property(CURRENT_DEFS COMPILE_DEFINITIONS)
    foreach(DEF ${CURRENT_DEFS})
        list(APPEND FLAGLIST "-D${DEF}")
    endforeach(DEF ${CURRENT_DEFS})

    # Append any include directories from the directory properties
    get_property(AIRLINER_BUILD_PREFIX GLOBAL PROPERTY AIRLINER_BUILD_PREFIX_PROPERTY)
    get_target_property(APP_INCS ${AIRLINER_BUILD_PREFIX}${APP_NAME} INCLUDE_DIRECTORIES)
    foreach(INC ${APP_INCS})
        list(APPEND FLAGLIST "-I${INC}")
    endforeach(INC ${APP_INCS})

    get_directory_property(CURRENT_INCDIRS INCLUDE_DIRECTORIES)
    foreach(INC ${CURRENT_INCDIRS})
        list(APPEND FLAGLIST "-I${INC}")
    endforeach(INC ${CURRENT_INCDIRS})

    set(${OUTPUT_LIST} ${FLAGLIST} PARENT_SCOPE)

endfunction(psp_get_app_cflags OUTPUT_LIST INPUT_FLAGS)



function(psp_add_airliner_app_table)
    set(PARSED_ARGS_TARGET ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS "" "NAME" "SOURCES;INCLUDES" ${ARGN})
    
    get_property(AIRLINER_BUILD_PREFIX GLOBAL PROPERTY AIRLINER_BUILD_PREFIX_PROPERTY)

    psp_get_app_cflags(${PARSED_ARGS_TARGET} TBL_CFLAGS ${CMAKE_C_FLAGS})

    add_custom_command(
        OUTPUT ${PARSED_ARGS_NAME}.tbl
        COMMAND ${CMAKE_C_COMPILER} ${TBL_CFLAGS} -c -o ${PARSED_ARGS_NAME}.o ${PARSED_ARGS_SOURCES}
        COMMAND ${PROJECT_BINARY_DIR}/host/tools/elf2cfetbl/elf2cfetbl ${PARSED_ARGS_NAME}.o
        COMMAND cp ${PARSED_ARGS_NAME}.tbl ${INSTALL_DIR}
        BYPRODUCTS ${PARSED_ARGS_NAME}.tbl
        DEPENDS ${PARSED_ARGS_SOURCES}
    )
    add_custom_target(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_NAME} ALL
        DEPENDS ${PARSED_ARGS_NAME}.tbl ${PARSED_ARGS_SOURCES} elf2cfetbl
    )
endfunction(psp_add_airliner_app_table)

