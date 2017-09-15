# Copy nanopb from the tools directory to apps/pblib
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../nanopb/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Find SCons
find_program(scons_path scons)

# Check that the SCons build system is installed
if(NOT scons_path)
    message(SEND_ERROR "scons not found!")
endif()

set(nanopb_tests_path ${CMAKE_CURRENT_BINARY_DIR}/tests)

# Build and run nanopb tests
#add_custom_target(nanopb
    #ALL
    #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tests
    #COMMAND scons 
#)

add_test(NAME nanopb-all-tests
         COMMAND ${scons_path} -s -C ${nanopb_tests_path})
