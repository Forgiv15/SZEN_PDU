# The following variables contains the files used by the different stages of the build process.
set(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_assemble)
set_source_files_properties(${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_assembleWithPreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/exceptions.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/initialization.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/interrupts.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/libc_syscalls.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/adc/plib_adc0.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/adc/plib_adc1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/can/plib_can0.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/can/plib_can1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/clock/plib_clock.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/evsys/plib_evsys.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/nvic/plib_nvic.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/nvmctrl/plib_nvmctrl.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/port/plib_port.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/sercom/i2c_master/plib_sercom1_i2c_master.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/systick/plib_systick.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/peripheral/tc/plib_tc0.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/startup_xc32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/stdio/xc32_monitor.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/linear11.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/pdu.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/pdu_adc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/pmbus.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/pmbus_pec.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/tps25990.c")
set_source_files_properties(${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_compile_cpp)
set_source_files_properties(${SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_link)
set(SZEN_PDU_0_1_default_default_XC32_FILE_TYPE_bin2hex)

# The linker script used for the build.
set(SZEN_PDU_0_1_default_LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/../../../My_MCC_Config/src/config/default/PIC32CM5164JH01064.ld")
set(SZEN_PDU_0_1_default_image_name "default.elf")
set(SZEN_PDU_0_1_default_image_base_name "default")

# The output directory of the final image.
set(SZEN_PDU_0_1_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/SZEN_PDU_0.1")

# The full path to the final image.
set(SZEN_PDU_0_1_default_full_path_to_image ${SZEN_PDU_0_1_default_output_dir}/${SZEN_PDU_0_1_default_image_name})
