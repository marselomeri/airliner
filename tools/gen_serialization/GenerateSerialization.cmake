function(generate_serialization_code)
    # Define the function arguments.
    cmake_parse_arguments(PARSED_ARGS "" "INPUT_FILE;OPS_FILE;MSGS_FILE;OUTPUT_DIR" "" ${ARGN})

    if(EXISTS ${PARSED_ARGS_MSGS_FILE})
        if(NOT EXISTS "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json")
            file(WRITE "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json" "{}")
        endif(NOT EXISTS "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json")
    
        add_custom_target(gen_serialization 
            DEPENDS explain_cookie 
            
            COMMAND $ENV{AIRLINER_ROOT}/tools/gen_serialization/generate
                ${PARSED_ARGS_INPUT_FILE}
                ${PARSED_ARGS_OUTPUT_DIR} 
            	
            COMMAND $ENV{AIRLINER_ROOT}/tools/commander/merge.js 
                -a ${PARSED_ARGS_INPUT_FILE}
                -b ${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json
                -o ${PARSED_ARGS_OUTPUT_DIR}/airliner.json
        )
            
        add_dependencies(ground_tools gen_serialization)
    endif()
    
endfunction(generate_serialization_code)


function(add_airliner_json_input)
    set(TARGET_NAME ${ARGV0})
    
    # Define the function arguments.
    cmake_parse_arguments(PARSED_ARGS "" "INPUT_FILE;OUTPUT_DIR" "" ${ARGN})
    
    #if(EXISTS ${PARSED_ARGS_INPUT_FILE})
        if(NOT EXISTS "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json")
            file(WRITE "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json" "{}")
        endif(NOT EXISTS "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json")
        
        execute_process(
            COMMAND $ENV{AIRLINER_ROOT}/tools/commander/merge.js 
            	-a ${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json
            	-b ${PARSED_ARGS_INPUT_FILE} 
            	-o ${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json
        )
    #endif()
    
endfunction(add_airliner_json_input)

