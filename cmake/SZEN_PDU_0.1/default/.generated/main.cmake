include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(SZEN_PDU_0_1_default_library_list )

# Handle files with suffix s, for group default-XC32
if(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_assemble)
add_library(SZEN_PDU_0_1_default_default_XC32_assemble OBJECT ${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_assemble})
    SZEN_PDU_0_1_default_default_XC32_assemble_rule(SZEN_PDU_0_1_default_default_XC32_assemble)
    list(APPEND SZEN_PDU_0_1_default_library_list "$<TARGET_OBJECTS:SZEN_PDU_0_1_default_default_XC32_assemble>")

endif()

# Handle files with suffix S, for group default-XC32
if(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
add_library(SZEN_PDU_0_1_default_default_XC32_assembleWithPreprocess OBJECT ${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_assembleWithPreprocess})
    SZEN_PDU_0_1_default_default_XC32_assembleWithPreprocess_rule(SZEN_PDU_0_1_default_default_XC32_assembleWithPreprocess)
    list(APPEND SZEN_PDU_0_1_default_library_list "$<TARGET_OBJECTS:SZEN_PDU_0_1_default_default_XC32_assembleWithPreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC32
if(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_compile)
add_library(SZEN_PDU_0_1_default_default_XC32_compile OBJECT ${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_compile})
    SZEN_PDU_0_1_default_default_XC32_compile_rule(SZEN_PDU_0_1_default_default_XC32_compile)
    list(APPEND SZEN_PDU_0_1_default_library_list "$<TARGET_OBJECTS:SZEN_PDU_0_1_default_default_XC32_compile>")

endif()

# Handle files with suffix cpp, for group default-XC32
if(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_compile_cpp)
add_library(SZEN_PDU_0_1_default_default_XC32_compile_cpp OBJECT ${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_compile_cpp})
    SZEN_PDU_0_1_default_default_XC32_compile_cpp_rule(SZEN_PDU_0_1_default_default_XC32_compile_cpp)
    list(APPEND SZEN_PDU_0_1_default_library_list "$<TARGET_OBJECTS:SZEN_PDU_0_1_default_default_XC32_compile_cpp>")

endif()

# Handle files with suffix [cC], for group default-XC32
if(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_dependentObject)
add_library(SZEN_PDU_0_1_default_default_XC32_dependentObject OBJECT ${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_dependentObject})
    SZEN_PDU_0_1_default_default_XC32_dependentObject_rule(SZEN_PDU_0_1_default_default_XC32_dependentObject)
    list(APPEND SZEN_PDU_0_1_default_library_list "$<TARGET_OBJECTS:SZEN_PDU_0_1_default_default_XC32_dependentObject>")

endif()

# Handle files with suffix elf, for group default-XC32
if(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_bin2hex)
add_library(SZEN_PDU_0_1_default_default_XC32_bin2hex OBJECT ${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_bin2hex})
    SZEN_PDU_0_1_default_default_XC32_bin2hex_rule(SZEN_PDU_0_1_default_default_XC32_bin2hex)
    list(APPEND SZEN_PDU_0_1_default_library_list "$<TARGET_OBJECTS:SZEN_PDU_0_1_default_default_XC32_bin2hex>")

endif()


# Main target for this project
add_executable(SZEN_PDU_0_1_default_image_gPQ6L7Jj ${SZEN_PDU_0_1_default_library_list})

set_target_properties(SZEN_PDU_0_1_default_image_gPQ6L7Jj PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    RUNTIME_OUTPUT_DIRECTORY "${SZEN_PDU_0_1_default_output_dir}")
target_link_libraries(SZEN_PDU_0_1_default_image_gPQ6L7Jj PRIVATE ${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_link})

# Add the link options from the rule file.
SZEN_PDU_0_1_default_link_rule( SZEN_PDU_0_1_default_image_gPQ6L7Jj)

# Call bin2hex function from the rule file
SZEN_PDU_0_1_default_bin2hex_rule(SZEN_PDU_0_1_default_image_gPQ6L7Jj)

