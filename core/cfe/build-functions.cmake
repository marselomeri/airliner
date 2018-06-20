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
 
set(CFE_PSP_DIR "")
set(CFE_OSAL_DIR "")

#build_airliner_cfe(
#    PREFIX 
#    PSP    pc-linux
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
function(build_airliner_cfe)
    # Define the function arguments.
    cmake_parse_arguments(PARSED_ARGS "" "PREFIX;PSP;OSAL;STARTUP_SCRIPT;UNIT_TEST_WRAPPER" "CONFIG;FILESYS" ${ARGN})
    
    # Reset the global variables that are only global to a CFS build.
    set_property(GLOBAL PROPERTY PUBLIC_APP_INCLUDES_PROPERTY "")
    set_property(GLOBAL PROPERTY AIRLINER_BUILD_PREFIX_PROPERTY ${PARSED_ARGS_PREFIX})
    
    set(UNIT_TEST_WRAPPER ${PARSED_ARGS_UNIT_TEST_WRAPPER})
    
    define_property(TARGET PROPERTY USER_DOCS_INPUT
        BRIEF_DOCS "Doxygen input file for user documentation."
        FULL_DOCS "Doxygen input file for user documentation.")
    
    define_property(TARGET PROPERTY DESIGN_DOCS_INPUT
        BRIEF_DOCS "Doxygen input file for user documentation."
        FULL_DOCS "Doxygen input file for design documentation.")
    
    define_property(TARGET PROPERTY APP_DEFINITION_DIR
        BRIEF_DOCS "Application definition directory."
        FULL_DOCS "Application definition directory.")
    
    define_property(TARGET PROPERTY APP_DEFINITION_SRC
        BRIEF_DOCS "Application definition source files."
        FULL_DOCS "Application definition source files.")
    
    define_property(TARGET PROPERTY APP_CONFIG_SRC
        BRIEF_DOCS "Application configuration source files."
        FULL_DOCS "Application configuration source files.")
            
    set(CFS_DOCS_DIR ${CMAKE_BINARY_DIR}/docs)
    set(CFS_DOCS_HTML_DIR ${CFS_DOCS_DIR}/html)
    
    add_subdirectory(${PARSED_ARGS_PSP}/src psp/platform)
    add_subdirectory(${PSP_SHARED_DIR} psp/shared)

    set(CFE_PSP_DIR ${PARSED_ARGS_PSP})
    set(CFE_OSAL_DIR ${PARSED_ARGS_OSAL})

    include(${PARSED_ARGS_PSP}/make/build-vars.cmake)
    include(${PARSED_ARGS_PSP}/make/build-functions.cmake)
    
    set_global_airliner_includes(${PARSED_ARGS_CONFIG})
    
    # Parse the various CFE component CMake files that will specify the various source files.
    add_subdirectory(${CFE_CORE_SRC}/make cfe)
    
    psp_build_airliner_cfe(${ARGN})
    
    set(CFS_DOCS_DIR ${CFS_DOCS_DIR} PARENT_SCOPE)
    set(CFS_DOCS_HTML_DIR ${CFS_DOCS_HTML_DIR} PARENT_SCOPE)
    set(MEMCHECK_COMMAND ${MEMCHECK_COMMAND} PARENT_SCOPE)
    set(HELGRIND_COMMAND ${HELGRIND_COMMAND} PARENT_SCOPE)
    set(MASSIF_COMMAND ${MASSIF_COMMAND} PARENT_SCOPE)
    set(UNIT_TEST_WRAPPER ${UNIT_TEST_WRAPPER} PARENT_SCOPE)
endfunction(build_airliner_cfe)



#add_airliner_app(
#    DEFINITION
#        ${PROJECT_SOURCE_DIR}/apps/cfs_lib
#    CONFIG
#        ${CMAKE_CURRENT_SOURCE_DIR}/apps/cfs_lib
#)
# This function doesn't actually add the application.  It calls the CMakeLists.txt in the application source directory,
# which actually adds the application.
function(add_airliner_app)
    # Define the application name.
    set(PARSED_ARGS_APP_NAME ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS "" "DEFINITION" "CONFIG" ${ARGN})

    psp_add_airliner_app(${ARGN})

endfunction(add_airliner_app)



#build_airliner_cfe_host_tools(
#    PSP pc-linux
#    OSAL posix
#    CONFIG
#        ${CMAKE_CURRENT_SOURCE_DIR}/inc
#        ${CMAKE_CURRENT_SOURCE_DIR}/../../shared/inc
#)
# Build all the host tools.  Currently, this is just the elf2cfetbl.
function(build_airliner_cfe_host_tools)
    cmake_parse_arguments(PARSED_ARGS "" "PREFIX;TARGET_PSP;TARGET_OSAL;HOST_PSP;HOST_OSAL;STARTUP_SCRIPT" "CONFIG;CONFIG_SOURCES;FILESYS" ${ARGN})
 
#    include(${PARSED_ARGS_HOST_PSP}/make/build-vars.cmake)
#    include(${PARSED_ARGS_HOST_PSP}/make/build-functions.cmake)   
     
#    build_airliner_cfe(
#        PREFIX gndnode-
#        PSP ${PARSED_ARGS_HOST_PSP}
#        OSAL ${PARSED_ARGS_HOST_OSAL}
#        CONFIG
#            ${PARSED_ARGS_CONFIG};
#        FILESYS
#            ${PARSED_ARGS_FILESYS};
#        STARTUP_SCRIPT
#            ${PARSED_ARGS_STARTUP_SCRIPT};
#        CONFIG_SOURCES
#            ${PARSED_ARGS_CONFIG_SOURCES};
#    )
    
    add_subdirectory(${CFE_TOOLS}/elf2cfetbl ${ELF2CFETBL_BIN})
    
    set_property(GLOBAL PROPERTY AIRLINER_BUILD_PREFIX ${PARSED_ARGS_PREFIX})
endfunction(build_airliner_cfe_host_tools)


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
function(add_airliner_app_def)
    set(PARSED_ARGS_TARGET ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS "" "FILE;PREFIX" "SOURCES;LIBS;INCLUDES;PUBLIC_INCLUDES;USER_DOCS;DESIGN_DOCS" ${ARGN})

    psp_add_airliner_app_def(${ARGN})
endfunction(add_airliner_app_def)



function(add_airliner_app_src)
    set(PARSED_ARGS_TARGET ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS "" "" "SOURCES" ${ARGN})

    target_sources(${PARSED_ARGS_TARGET} PUBLIC ${PARSED_ARGS_SOURCES})

endfunction(add_airliner_app_src)



function(add_airliner_app_unit_test_src)
    set(PARSED_ARGS_TARGET ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS "" "" "SOURCES" ${ARGN})

    get_property(AIRLINER_BUILD_PREFIX GLOBAL PROPERTY AIRLINER_BUILD_PREFIX_PROPERTY)
    target_sources(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET} PUBLIC ${PARSED_ARGS_SOURCES})
    target_sources(${AIRLINER_BUILD_PREFIX}${PARSED_ARGS_TARGET}-gcov PUBLIC ${PARSED_ARGS_SOURCES})

endfunction(add_airliner_app_unit_test_src)



function(add_airliner_app_unit_test)
    set(PARSED_ARGS_TARGET ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS "UTF;UTASSERT" "FILE;VALGRIND_SUPPRESSION_FILE" "SOURCES;LIBS;INCLUDES;WRAPPERS" ${ARGN})

    psp_add_airliner_app_unit_test(${ARGN})
endfunction(add_airliner_app_unit_test)



function(add_airliner_cfe_unit_test)
    set(PARSED_ARGS_TARGET ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS "" "VALGRIND_SUPPRESSION_FILE" "SOURCES;INCLUDES" ${ARGN})
    
    psp_add_airliner_cfe_unit_test(${ARGN})
endfunction(add_airliner_cfe_unit_test)



#function(JOIN VALUES GLUE OUTPUT)
#    string (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
#    string (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
#    set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
#endfunction()



function(add_airliner_app_table)
    set(PARSED_ARGS_TARGET ${ARGV0})
    cmake_parse_arguments(PARSED_ARGS "" "NAME" "SOURCES;INCLUDES" ${ARGN})

    psp_add_airliner_app_table(${ARGN})

endfunction(add_airliner_app_table)

