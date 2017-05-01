# The build system is tested with cmake version 3.5.2
cmake_minimum_required(VERSION 3.5.2)

# Set paths from all 3 major core components:  CFE, OSAL, and PSP.
include(cfe/set-paths.cmake)
include(osal/set-paths.cmake)
include(psp/set-paths.cmake)

# Set the path to elf2cfetbl here since we build it in the host phase, but use it in the target phase.
set(ELF2CFETBL_BIN ${PROJECT_BINARY_DIR}/tools/elf2cfetbl)

# Include the file with all the build functions that we will call in the configuration directory.
include(${CMAKE_CURRENT_SOURCE_DIR}/cfe/fsw/src/make/build-functions.cmake)

# Make sure we don't go any further unless the caller specified the BUILD_TARGET
if(NOT DEFINED BUILD_TARGET)
    error("No build target set.  You must add either -DBUILD_TARGET:STRING=HOST or -DBUILD_TARGET:STRING=HOST.")
endif()

# Now, start building with the configuration.
add_subdirectory(config/${BUILDNAME} config)

