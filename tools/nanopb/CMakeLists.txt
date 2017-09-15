
add_custom_target(nanopb
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
    COMMAND scons
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/build/alltypes/encode_alltypes
)

add_test(nanopb-encode-alltypes ${CMAKE_CURRENT_SOURCE_DIR}/tests/build/alltypes/encode_alltypes)