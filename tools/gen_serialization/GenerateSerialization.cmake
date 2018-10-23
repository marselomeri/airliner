function(generate_serialization_code)
    # Define the function arguments.
    cmake_parse_arguments(PARSED_ARGS "" "INPUT_FILE;OPS_FILE;MSGS_FILE;OUTPUT_DIR" "" ${ARGN})
    
    if(NOT EXISTS "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json")
        file(WRITE "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json" "{}")
    endif(NOT EXISTS "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json")
    
    add_custom_target(setup_commander
	    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tools/commander
	    COMMAND npm install
    )
    
    add_custom_target(gen_serialization 
        DEPENDS explain_cookie setup_commander all_merge_json
        
        COMMAND ${PROJECT_SOURCE_DIR}/tools/gen_serialization/generate
         	${PARSED_ARGS_INPUT_FILE}
        	${PARSED_ARGS_OUTPUT_DIR} 
        	
        COMMAND ${PROJECT_SOURCE_DIR}/tools/commander/merge.js 
        	-a ${PARSED_ARGS_INPUT_FILE}
        	-b ${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json
        	-o ${PARSED_ARGS_OUTPUT_DIR}/airliner.json
    )

    add_dependencies(ground_tools gen_serialization)
    
endfunction(generate_serialization_code)


function(add_airliner_json_input)
    set(TARGET_NAME ${ARGV0})
    
    # Define the function arguments.
    cmake_parse_arguments(PARSED_ARGS "" "INPUT_FILE;OUTPUT_DIR" "" ${ARGN})
    
    if(NOT EXISTS "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json")
        file(WRITE "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json" "{}")
    endif(NOT EXISTS "${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json")
    
    if(NOT TARGET all_merge_json)
        add_custom_target(all_merge_json)
    endif(NOT TARGET all_merge_json)
    
    add_custom_target(${TARGET_NAME}_merge_JSON
        DEPENDS setup_commander
        COMMAND ${PROJECT_SOURCE_DIR}/tools/commander/merge.js 
        	-a ${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json
        	-b ${PARSED_ARGS_INPUT_FILE} 
        	-o ${PARSED_ARGS_OUTPUT_DIR}/airliner-overrides.json
    )
    add_dependencies(all_merge_json ${TARGET_NAME}_merge_JSON)
    
endfunction(add_airliner_json_input)

