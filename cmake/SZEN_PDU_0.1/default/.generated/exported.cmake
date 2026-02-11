set(DEPENDENT_MP_BIN2HEXSZEN_PDU_0_1_default_gPQ6L7Jj "c:/Program Files/Microchip/xc32/v5.00/bin/xc32-bin2hex.exe")
set(DEPENDENT_DEPENDENT_TARGET_ELFSZEN_PDU_0_1_default_gPQ6L7Jj ${CMAKE_CURRENT_LIST_DIR}/../../../../out/SZEN_PDU_0.1/default.elf)
set(DEPENDENT_TARGET_DIRSZEN_PDU_0_1_default_gPQ6L7Jj ${CMAKE_CURRENT_LIST_DIR}/../../../../out/SZEN_PDU_0.1)
set(DEPENDENT_BYPRODUCTSSZEN_PDU_0_1_default_gPQ6L7Jj ${DEPENDENT_TARGET_DIRSZEN_PDU_0_1_default_gPQ6L7Jj}/${sourceFileNameSZEN_PDU_0_1_default_gPQ6L7Jj}.c)
add_custom_command(
    OUTPUT ${DEPENDENT_TARGET_DIRSZEN_PDU_0_1_default_gPQ6L7Jj}/${sourceFileNameSZEN_PDU_0_1_default_gPQ6L7Jj}.c
    COMMAND ${DEPENDENT_MP_BIN2HEXSZEN_PDU_0_1_default_gPQ6L7Jj} --image ${DEPENDENT_DEPENDENT_TARGET_ELFSZEN_PDU_0_1_default_gPQ6L7Jj} --image-generated-c ${sourceFileNameSZEN_PDU_0_1_default_gPQ6L7Jj}.c --image-generated-h ${sourceFileNameSZEN_PDU_0_1_default_gPQ6L7Jj}.h --image-copy-mode ${modeSZEN_PDU_0_1_default_gPQ6L7Jj} --image-offset ${addressSZEN_PDU_0_1_default_gPQ6L7Jj} 
    WORKING_DIRECTORY ${DEPENDENT_TARGET_DIRSZEN_PDU_0_1_default_gPQ6L7Jj}
    DEPENDS ${DEPENDENT_DEPENDENT_TARGET_ELFSZEN_PDU_0_1_default_gPQ6L7Jj})
add_custom_target(
    dependent_produced_source_artifactSZEN_PDU_0_1_default_gPQ6L7Jj 
    DEPENDS ${DEPENDENT_TARGET_DIRSZEN_PDU_0_1_default_gPQ6L7Jj}/${sourceFileNameSZEN_PDU_0_1_default_gPQ6L7Jj}.c
    )
