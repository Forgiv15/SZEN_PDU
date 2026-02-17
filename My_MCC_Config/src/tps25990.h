/**
 * @file tps25990.h
 * @brief TPS25990 eFuse driver interface for PMBus telemetry and control
 * 
 * Provides structures and functions for communicating with TPS25990 eFuse
 * devices via PMBus, including full STATUS_WORD decoding.
 */

#ifndef TPS25990_H
#define TPS25990_H

#include <stdint.h>
#include <stdbool.h>

/*============================================================================
 * TPS25990 PMBus Command Codes
 *===========================================================================*/

/* Standard PMBus Telemetry Commands */
#define TPS25990_CMD_STATUS_WORD    0x79U
#define TPS25990_CMD_STATUS_BYTE    0x78U
#define TPS25990_CMD_STATUS_VOUT    0x7AU
#define TPS25990_CMD_STATUS_IOUT    0x7BU
#define TPS25990_CMD_STATUS_IN      0x7CU
#define TPS25990_CMD_STATUS_TEMP    0x7DU
#define TPS25990_CMD_STATUS_CML     0x7EU
#define TPS25990_CMD_STATUS_MFR     0x80U
#define TPS25990_CMD_READ_VIN       0x88U
#define TPS25990_CMD_READ_VOUT      0x8BU
#define TPS25990_CMD_READ_IIN       0x89U
#define TPS25990_CMD_READ_PIN       0x97U
#define TPS25990_CMD_READ_TEMP      0x8DU

/*============================================================================
 * STATUS_WORD Bit Definitions (0x79)
 * 
 * STATUS_WORD is a 16-bit register where:
 * - Bits [7:0] = STATUS_BYTE (low byte)
 * - Bits [15:8] = High byte with additional status
 *===========================================================================*/

/* STATUS_WORD High Byte (bits 15:8) */
#define TPS25990_STATUS_WORD_VOUT           (1U << 15)  /* VOUT status (reserved) */
#define TPS25990_STATUS_WORD_IOUT           (1U << 14)  /* IOUT/POUT fault/warning */
#define TPS25990_STATUS_WORD_INPUT          (1U << 13)  /* INPUT status (VIN_UV, VIN_OV, OC) */
#define TPS25990_STATUS_WORD_MFR            (1U << 12)  /* MFR_SPECIFIC status */
#define TPS25990_STATUS_WORD_PGOODB         (1U << 11)  /* Power Good status (active low) */
#define TPS25990_STATUS_WORD_RESERVED_10    (1U << 10)  /* Reserved */
#define TPS25990_STATUS_WORD_FET_OFF        (1U << 9)   /* Output FET is OFF */
#define TPS25990_STATUS_WORD_RESERVED_8     (1U << 8)   /* Reserved */

/* STATUS_WORD Low Byte / STATUS_BYTE (bits 7:0) */
#define TPS25990_STATUS_BYTE_BUSY           (1U << 7)   /* Device busy */
#define TPS25990_STATUS_BYTE_FET_OFF        (1U << 6)   /* Output FET is OFF */
#define TPS25990_STATUS_BYTE_VOUT_OV        (1U << 5)   /* VOUT overvoltage (reserved) */
#define TPS25990_STATUS_BYTE_IOUT_OC        (1U << 4)   /* IOUT overcurrent */
#define TPS25990_STATUS_BYTE_VIN_UV         (1U << 3)   /* VIN undervoltage */
#define TPS25990_STATUS_BYTE_TEMP           (1U << 2)   /* Temperature fault/warning */
#define TPS25990_STATUS_BYTE_CML            (1U << 1)   /* Communication fault */
#define TPS25990_STATUS_BYTE_NONE_ABOVE     (1U << 0)   /* None of the above (other fault) */

/*============================================================================
 * STATUS_BYTE Bit Definitions (0x78)
 *===========================================================================*/

#define TPS25990_SB_BUSY            (1U << 7)   /* Device busy */
#define TPS25990_SB_FET_OFF         (1U << 6)   /* Output FET is OFF */
#define TPS25990_SB_VOUT_OV         (1U << 5)   /* VOUT overvoltage (reserved) */
#define TPS25990_SB_IOUT_OC         (1U << 4)   /* IOUT overcurrent */
#define TPS25990_SB_VIN_UV          (1U << 3)   /* VIN undervoltage */
#define TPS25990_SB_TEMP            (1U << 2)   /* Temperature fault/warning */
#define TPS25990_SB_CML             (1U << 1)   /* Communication fault */
#define TPS25990_SB_NONE_ABOVE      (1U << 0)   /* None of the above */

/*============================================================================
 * STATUS_IOUT Bit Definitions (0x7B)
 *===========================================================================*/

#define TPS25990_SIOUT_OC_FLT       (1U << 7)   /* Output overcurrent fault */
#define TPS25990_SIOUT_OC_LV_FLT    (1U << 6)   /* Output overcurrent low-voltage fault */
#define TPS25990_SIOUT_OC_WARN      (1U << 5)   /* Output overcurrent warning */
#define TPS25990_SIOUT_RESERVED_4   (1U << 4)   /* Reserved */
#define TPS25990_SIOUT_CL           (1U << 3)   /* Unit is in current limit mode */
#define TPS25990_SIOUT_RESERVED_2   (1U << 2)   /* Reserved */
#define TPS25990_SIOUT_POUT_OP_FLT  (1U << 1)   /* Output overpower fault */
#define TPS25990_SIOUT_POUT_OP_WARN (1U << 0)   /* Output overpower warning */

/*============================================================================
 * STATUS_TEMP Bit Definitions (0x7D)
 *===========================================================================*/

#define TPS25990_STEMP_OT_FLT       (1U << 7)   /* Overtemperature fault */
#define TPS25990_STEMP_OT_WARN      (1U << 6)   /* Overtemperature warning */
#define TPS25990_STEMP_RESERVED_5   (1U << 5)   /* Reserved */
#define TPS25990_STEMP_RESERVED_4   (1U << 4)   /* Reserved */
#define TPS25990_STEMP_RESERVED_3   (1U << 3)   /* Reserved */
#define TPS25990_STEMP_RESERVED_2   (1U << 2)   /* Reserved */
#define TPS25990_STEMP_RESERVED_1   (1U << 1)   /* Reserved */
#define TPS25990_STEMP_RESERVED_0   (1U << 0)   /* Reserved */

/*============================================================================
 * STATUS_IN Bit Definitions (0x7C) - Input Status
 *===========================================================================*/

#define TPS25990_SIN_VIN_OV_FLT     (1U << 7)   /* VIN overvoltage fault */
#define TPS25990_SIN_VIN_OV_WARN    (1U << 6)   /* VIN overvoltage warning */
#define TPS25990_SIN_VIN_UV_WARN    (1U << 5)   /* VIN undervoltage warning */
#define TPS25990_SIN_OC_FLT         (1U << 4)   /* Input overcurrent fault (circuit breaker) */
#define TPS25990_SIN_VIN_UV_FLT     (1U << 3)   /* VIN undervoltage fault */
#define TPS25990_SIN_RESERVED_2     (1U << 2)   /* Reserved */
#define TPS25990_SIN_RESERVED_1     (1U << 1)   /* Reserved */
#define TPS25990_SIN_RESERVED_0     (1U << 0)   /* Reserved */

/*============================================================================
 * STATUS_CML Bit Definitions (0x7E) - Communication/Logic Fault
 *===========================================================================*/

#define TPS25990_SCML_INV_CMD       (1U << 7)   /* Invalid or unsupported command */
#define TPS25990_SCML_INV_DATA      (1U << 6)   /* Invalid or unsupported data */
#define TPS25990_SCML_PEC_FAIL      (1U << 5)   /* PEC check failed */
#define TPS25990_SCML_MEM_FAULT     (1U << 4)   /* Memory fault detected */
#define TPS25990_SCML_PROC_FAULT    (1U << 3)   /* Processor fault */
#define TPS25990_SCML_RESERVED_2    (1U << 2)   /* Reserved */
#define TPS25990_SCML_COMM_FAULT    (1U << 1)   /* Communication fault (other) */
#define TPS25990_SCML_RESERVED_0    (1U << 0)   /* Reserved */

/*============================================================================
 * STATUS_MFR_SPECIFIC Bit Definitions (0x80)
 *===========================================================================*/

#define TPS25990_SMFR_SHORT_FLT     (1U << 7)   /* Short circuit fault */
#define TPS25990_SMFR_HOTSWAP       (1U << 6)   /* Hotswap event */
#define TPS25990_SMFR_FET_HEALTH    (1U << 5)   /* FET health monitor fault */
#define TPS25990_SMFR_RESERVED_4    (1U << 4)   /* Reserved */
#define TPS25990_SMFR_RESERVED_3    (1U << 3)   /* Reserved */
#define TPS25990_SMFR_RESERVED_2    (1U << 2)   /* Reserved */
#define TPS25990_SMFR_RESERVED_1    (1U << 1)   /* Reserved */
#define TPS25990_SMFR_RESERVED_0    (1U << 0)   /* Reserved */

/*============================================================================
 * Decoded Status Structures
 *===========================================================================*/

/**
 * @brief Decoded STATUS_BYTE fields
 */
typedef struct {
    bool busy;          /**< Device is busy */
    bool fet_off;       /**< Output FET is off */
    bool vout_ov;       /**< VOUT overvoltage (reserved) */
    bool iout_oc;       /**< IOUT overcurrent */
    bool vin_uv;        /**< VIN undervoltage */
    bool temp_fault;    /**< Temperature fault or warning */
    bool cml_fault;     /**< Communication fault */
    bool other_fault;   /**< None of the above (other fault) */
} tps25990_status_byte_t;

/**
 * @brief Decoded STATUS_IOUT fields
 */
typedef struct {
    bool oc_fault;      /**< Overcurrent fault */
    bool oc_lv_fault;   /**< Overcurrent low-voltage fault */
    bool oc_warning;    /**< Overcurrent warning */
    bool current_limit; /**< In current limit mode */
    bool pout_op_fault; /**< Output overpower fault */
    bool pout_op_warn;  /**< Output overpower warning */
} tps25990_status_iout_t;

/**
 * @brief Decoded STATUS_TEMP fields
 */
typedef struct {
    bool ot_fault;      /**< Overtemperature fault */
    bool ot_warning;    /**< Overtemperature warning */
} tps25990_status_temp_t;

/**
 * @brief Decoded STATUS_IN (input) fields
 */
typedef struct {
    bool vin_ov_fault;  /**< VIN overvoltage fault */
    bool vin_ov_warn;   /**< VIN overvoltage warning */
    bool vin_uv_warn;   /**< VIN undervoltage warning */
    bool oc_fault;      /**< Input overcurrent fault (circuit breaker) */
    bool vin_uv_fault;  /**< VIN undervoltage fault */
} tps25990_status_in_t;

/**
 * @brief Decoded STATUS_CML (communication/logic) fields
 */
typedef struct {
    bool inv_cmd;       /**< Invalid command */
    bool inv_data;      /**< Invalid data */
    bool pec_fail;      /**< PEC check failed */
    bool mem_fault;     /**< Memory fault */
    bool proc_fault;    /**< Processor fault */
    bool comm_fault;    /**< Communication fault */
} tps25990_status_cml_t;

/**
 * @brief Decoded STATUS_MFR_SPECIFIC fields
 */
typedef struct {
    bool short_fault;   /**< Short circuit fault */
    bool hotswap;       /**< Hotswap event */
    bool fet_health;    /**< FET health monitor fault */
} tps25990_status_mfr_t;

/**
 * @brief Complete decoded STATUS_WORD with high byte flags
 */
typedef struct {
    /* Raw values */
    uint16_t raw;               /**< Raw STATUS_WORD value */
    
    /* High byte flags */
    bool vout_status;           /**< VOUT status flag */
    bool iout_status;           /**< IOUT/POUT status flag */
    bool input_status;          /**< Input status flag */
    bool mfr_status;            /**< Manufacturer-specific status */
    bool pgoodb;                /**< Power good status (0=good) */
    bool fet_off_hi;            /**< FET OFF from high byte */
    
    /* Low byte (STATUS_BYTE) decoded */
    tps25990_status_byte_t status_byte;
} tps25990_status_word_t;

/**
 * @brief Complete TPS25990 telemetry data structure
 */
typedef struct {
    /* Raw PMBus words (Linear11 format) */
    uint16_t status_word;
    uint16_t vin_raw;
    uint16_t vout_raw;
    uint16_t iin_raw;
    uint16_t pin_raw;
    uint16_t temp_raw;

    /* Decoded values (SI units) */
    float vin_V;        /**< Input voltage in Volts */
    float vout_V;       /**< Output voltage in Volts */
    float iin_A;        /**< Input current in Amps */
    float pin_W;        /**< Input power in Watts */
    float temp_C;       /**< Temperature in Celsius */

    /* Sanity check result */
    bool power_mismatch;    /**< True if P != V*I beyond tolerance */
} tps25990_data_t;

/**
 * @brief Complete TPS25990 status structure with all decoded registers
 */
typedef struct {
    tps25990_status_word_t word;    /**< Decoded STATUS_WORD */
    tps25990_status_iout_t iout;    /**< Decoded STATUS_IOUT */
    tps25990_status_temp_t temp;    /**< Decoded STATUS_TEMP */
    tps25990_status_in_t input;     /**< Decoded STATUS_IN */
    tps25990_status_cml_t cml;      /**< Decoded STATUS_CML */
    tps25990_status_mfr_t mfr;      /**< Decoded STATUS_MFR_SPECIFIC */
} tps25990_full_status_t;

/*============================================================================
 * Function Declarations
 *===========================================================================*/

/**
 * @brief Read all telemetry data from a TPS25990 device
 * 
 * @param addr 7-bit I2C device address
 * @param out Pointer to data structure to populate
 * @return true on success, false on communication error
 */
bool tps25990_read_all(uint8_t addr, tps25990_data_t *out);

/**
 * @brief Read and decode STATUS_WORD from a TPS25990 device
 * 
 * @param addr 7-bit I2C device address
 * @param out Pointer to decoded status structure
 * @return true on success, false on communication error
 */
bool tps25990_read_status_word(uint8_t addr, tps25990_status_word_t *out);

/**
 * @brief Read and decode all status registers from a TPS25990 device
 * 
 * @param addr 7-bit I2C device address
 * @param out Pointer to full status structure
 * @return true on success, false on communication error
 */
bool tps25990_read_full_status(uint8_t addr, tps25990_full_status_t *out);

/**
 * @brief Check if FET is currently on (output enabled)
 * 
 * @param addr 7-bit I2C device address
 * @return true if FET is ON, false if OFF or error
 */
bool tps25990_is_fet_on(uint8_t addr);

/**
 * @brief Turn on the eFuse output
 * 
 * @param addr 7-bit I2C device address
 * @return true on success, false on error
 */
bool tps25990_turn_on(uint8_t addr);

/**
 * @brief Turn off the eFuse output
 * 
 * @param addr 7-bit I2C device address
 * @return true on success, false on error
 */
bool tps25990_turn_off(uint8_t addr);

/**
 * @brief Clear all fault status bits
 * 
 * @param addr 7-bit I2C device address
 * @return true on success, false on error
 */
bool tps25990_clear_faults(uint8_t addr);

#endif /* TPS25990_H */