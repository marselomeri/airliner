# The build system is tested with cmake version 3.5.2
cmake_minimum_required(VERSION 3.0.0)

include(CTest)
find_program( MEMORYCHECK_COMMAND valgrind )
find_package(Threads)
set( CTEST_MEMORYCHECK_COMMAND_OPTIONS "--tool=memcheck --leak-check=full --show-reachable=yes --undef-value-errors=yes --track-origins=no --child-silent-after-fork=no --trace-children=no --xml=yes --xml-file=memcheck-%p.xml" )
set( CTEST_VALGRIND_COMMAND_OPTIONS "--tool=memcheck --leak-check=full --show-reachable=yes --undef-value-errors=yes --track-origins=no --child-silent-after-fork=no --trace-children=no --xml=yes --xml-file=memcheck-%p.xml")
enable_testing()

add_custom_target(docs)

# Set paths from all 3 major core components:  CFE, OSAL, and PSP.
include(cfe/set-paths.cmake)
include(osal/set-paths.cmake)
include(psp/set-paths.cmake)

# Set the path to elf2cfetbl here since we build it in the host phase, but use it in the target phase.
set(ELF2CFETBL_BIN ${PROJECT_BINARY_DIR}/host/tools/elf2cfetbl)

# Include the file with all the build functions that we will call in the configuration directory.
include(cfe/build-functions.cmake)

# Make sure we don't go any further unless the caller specified the BUILD_TARGET
if(NOT DEFINED BUILD_TARGET)
    error("No build target set.  You must add either -DBUILD_TARGET:STRING=HOST or -DBUILD_TARGET:STRING=HOST.")
endif()

# Now, start building with the configuration.
add_subdirectory(config/${BUILDNAME}/host host)
add_subdirectory(config/${BUILDNAME}/target target)

