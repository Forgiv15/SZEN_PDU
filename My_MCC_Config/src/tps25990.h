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

/* Default board assumption for IMON resistor scaling.
 * If your hardware uses a different R_IMON value, update this constant.
 */
#define TPS25990_DEFAULT_R_IMON_OHMS 1100.0f

/* Runtime configuration values used by this firmware. */
#define TPS25990_MFR_WRITE_PROTECT_LOCK    0x00U
#define TPS25990_MFR_WRITE_PROTECT_UNLOCK  0xA2U
#define TPS25990_DEVICE_CONFIG_OC_BLANK_MASK   (3U << 9)
#define TPS25990_DEVICE_CONFIG_OC_BLANK_K_1P5  (3U << 9)
#define TPS25990_DEVICE_CONFIG_SC_RETRY    (1U << 13)
#define TPS25990_RETRY_CONFIG_RESPONSE_MASK          (3U << 6)
#define TPS25990_RETRY_CONFIG_RESPONSE_SHUTDOWN_RETRY (2U << 6)
#define TPS25990_RETRY_CONFIG_COUNT_MASK            (7U << 3)
#define TPS25990_RETRY_CONFIG_COUNT_INDEFINITE      (7U << 3)
#define TPS25990_RETRY_CONFIG_DELAY_MASK            0x07U
#define TPS25990_RETRY_CONFIG_DELAY_55MS            0x00U
#define TPS25990_RETRY_CONFIG_DEFAULT      0x84U
#define TPS25990_RETRY_CONFIG_RACE_MODE    0x9BU
#define TPS25990_RETRY_CONFIG_TEST_MODE    0x96U

/* OC_TIMER (0xE6) – overcurrent blanking interval, bits [7:0] */
#define TPS25990_CMD_OC_TIMER           0xE6U
#define TPS25990_OC_TIMER_MAX_VALUE     0x77U

/* VIREF (0xE0) – internal reference voltage, bits [7:0] */
#define TPS25990_CMD_VIREF             0xE0U
#define TPS25990_VIREF_1V186_VALUE     0x3FU

/* PMBus threshold / warning commands used for TPS25990 */
#define TPS25990_CMD_VIN_UV_WARN        0x58U
#define TPS25990_CMD_VIN_UV_FLT         0x59U
#define TPS25990_CMD_OT_WARN            0x51U

/* PK_MIN_AVG (0xEA) – peak/min/average configuration */
#define TPS25990_CMD_PK_MIN_AVG         0xEAU
#define TPS25990_PK_MIN_AVG_AVG_CNT_MASK  0x07U
#define TPS25990_PK_MIN_AVG_AVG_CNT_128 0x07U

/* STATUS_TEMP (0x7D) bit definitions */
#define TPS25990_STATUS_TEMP_OT_FLT     (1U << 7)
#define TPS25990_STATUS_TEMP_OT_WARN    (1U << 6)

/* DIRECT-format pre‑computed threshold values */
/* VIN_UV_WARN at 9 V: m=13128 b=0 R=-3 => Y = (13128*9+0)/1000 ≈ 118 = 0x0076 */
#define TPS25990_VIN_UV_WARN_9V_VALUE   0x0076U
/* VIN_UV_FLT minimum (0 V): Y = 0 */
#define TPS25990_VIN_UV_FLT_MIN_VALUE   0x0000U
/* OT_WARN at 85 °C: m=35 b=8006 R=-2 => Y = (35*85+8006)/100 ≈ 110 = 0x006E */
#define TPS25990_OT_WARN_85C_VALUE      0x006EU

/* DEVICE_CONFIG (0xE4) bit‑field helpers */
#define TPS25990_DEVICE_CONFIG_SPFAIL_MASK    (3U << 11)
#define TPS25990_DEVICE_CONFIG_SPFAIL_225     (3U << 11)
#define TPS25990_DEVICE_CONFIG_DVDT_MASK      (3U << 9)
#define TPS25990_DEVICE_CONFIG_DVDT_SHIFT     9U
#define TPS25990_DEVICE_CONFIG_ADC_HI_PERF    (1U << 3)

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
 * STATUS_IN Bit Definitions (0x7C) - Input Status (TPS25990 specific)
 *===========================================================================*/

#define TPS25990_SIN_VIN_OV_FLT     (1U << 7)   /* VIN overvoltage fault */
#define TPS25990_SIN_VIN_OV_WARN    (1U << 6)   /* VIN overvoltage warning */
#define TPS25990_SIN_VIN_UV_WARN    (1U << 5)   /* VIN undervoltage warning */
#define TPS25990_SIN_VIN_UV_FLT     (1U << 4)   /* VIN undervoltage fault */
#define TPS25990_SIN_OC_FLT         (1U << 2)   /* Overcurrent fault (inrush & steady-state) */
#define TPS25990_SIN_OC_WARN        (1U << 1)   /* Overcurrent warning */
#define TPS25990_SIN_IN_OP_WARN     (1U << 0)   /* Overpower warning */

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
 * STATUS_MFR_SPECIFIC Bit Definitions (0x80) – TPS25990 specific
 *===========================================================================*/

#define TPS25990_SMFR_SHORT_FLT     (1U << 7)   /* Short circuit fault */
#define TPS25990_SMFR_HOTSWAP       (1U << 6)   /* Hotswap event */
#define TPS25990_SMFR_FET_HEALTH    (1U << 5)   /* FET health monitor fault */
#define TPS25990_SMFR_RESERVED_4    (1U << 4)   /* Reserved */
#define TPS25990_SMFR_SOA_FLT       (1U << 3)   /* FET SOA limit violation */
#define TPS25990_SMFR_EXT_FLT       (1U << 2)   /* External fault (SWEN pulled low) */
#define TPS25990_SMFR_RESERVED_1    (1U << 1)   /* Reserved */
#define TPS25990_SMFR_RESERVED_0    (1U << 0)   /* Reserved */

/*============================================================================
 * STATUS_MFR_SPECIFIC_2 Bit Definitions (0xF3, Read Word) – TPS25990 specific
 *===========================================================================*/

#define TPS25990_SMFR2_PGOODB          (1U << 13)  /* PGOOD pin status (0=good) */
#define TPS25990_SMFR2_SPFAIL          (1U << 12)  /* Single point failure (ILIM/IMON/IREF) */
#define TPS25990_SMFR2_SC_FLT          (1U << 11)  /* Short-circuit fault threshold crossed */
#define TPS25990_SMFR2_OC_DET          (1U << 10)  /* Overcurrent detected (inrush & steady-state) */
#define TPS25990_SMFR2_EIN_OF_WARN     (1U << 9)   /* EIN register overflow */
#define TPS25990_SMFR2_VIN_TRAN        (1U << 8)   /* VIN transient detected */
#define TPS25990_SMFR2_RETRY_REC       (1U << 3)   /* Fault recovery/retry status */
#define TPS25990_SMFR2_POWER_CYCLE_REC (1U << 2)   /* Power Cycle command recovery */
#define TPS25990_SMFR2_INIT_DONE       (1U << 1)   /* Register initialization complete */
#define TPS25990_SMFR2_CONFIG_NVM_STAT (1U << 0)   /* Configuration NVM available */

/*============================================================================
 * STATUS_OUT Bit Definitions (0x7A, Read Byte) – TPS25990 specific
 *===========================================================================*/

#define TPS25990_SOUT_VOUT_UV_WARN  (1U << 5)   /* VOUT undervoltage warning */

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
 * @brief Decoded STATUS_IN (input) fields – TPS25990 specific
 */
typedef struct {
    bool vin_ov_fault;  /**< VIN overvoltage fault */
    bool vin_ov_warn;   /**< VIN overvoltage warning */
    bool vin_uv_warn;   /**< VIN undervoltage warning */
    bool vin_uv_fault;  /**< VIN undervoltage fault */
    bool oc_fault;      /**< Overcurrent fault (inrush & steady-state) */
    bool oc_warn;       /**< Overcurrent warning */
    bool in_op_warn;    /**< Overpower warning */
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
 * @brief Decoded STATUS_MFR_SPECIFIC fields – TPS25990 specific
 */
typedef struct {
    bool short_fault;   /**< Short circuit fault */
    bool hotswap;       /**< Hotswap event */
    bool fet_health;    /**< FET health monitor fault */
    bool soa_flt;       /**< FET SOA limit violation */
    bool ext_flt;       /**< External fault (SWEN pulled low) */
} tps25990_status_mfr_t;

/**
 * @brief Decoded STATUS_MFR_SPECIFIC_2 fields (0xF3, Read Word)
 */
typedef struct {
    bool pgoodb;            /**< PGOOD pin status (0=good) */
    bool spfail;            /**< Single point failure (ILIM/IMON/IREF) */
    bool sc_flt;            /**< Short-circuit fault threshold crossed */
    bool oc_det;            /**< Overcurrent detected (inrush & steady-state) */
    bool ein_of_warn;       /**< EIN register overflow */
    bool vin_tran;          /**< VIN transient detected */
    bool retry_rec;         /**< Fault recovery/retry status */
    bool power_cycle_rec;   /**< Power Cycle command recovery */
    bool init_done;         /**< Register initialization complete */
    bool config_nvm_stat;   /**< Configuration NVM available */
} tps25990_status_mfr2_t;

/**
 * @brief Decoded STATUS_OUT fields (0x7A, Read Byte)
 */
typedef struct {
    bool vout_uv_warn;  /**< VOUT undervoltage warning */
} tps25990_status_out_t;

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
    /* Raw PMBus words (DIRECT format) */
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
    tps25990_status_word_t word;        /**< Decoded STATUS_WORD */
    tps25990_status_iout_t iout;        /**< Decoded STATUS_IOUT */
    tps25990_status_temp_t temp;        /**< Decoded STATUS_TEMP */
    tps25990_status_in_t input;         /**< Decoded STATUS_IN */
    tps25990_status_cml_t cml;          /**< Decoded STATUS_CML */
    tps25990_status_mfr_t mfr;          /**< Decoded STATUS_MFR_SPECIFIC */
    tps25990_status_mfr2_t mfr2;        /**< Decoded STATUS_MFR_SPECIFIC_2 */
    tps25990_status_out_t status_out;   /**< Decoded STATUS_OUT */
    uint16_t raw_mfr2;                  /**< Raw STATUS_MFR_SPECIFIC_2 value */
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
bool tps25990_read_all_with_r_imon(uint8_t addr, float r_imon_ohms, tps25990_data_t *out);

float tps25990_decode_vin(uint16_t raw);
float tps25990_decode_vout(uint16_t raw);
float tps25990_decode_iin(uint16_t raw);
float tps25990_decode_pin(uint16_t raw);
float tps25990_decode_temp(uint16_t raw);
float tps25990_decode_iin_with_r_imon(uint16_t raw, float r_imon_ohms);
float tps25990_decode_pin_with_r_imon(uint16_t raw, float r_imon_ohms);

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
bool tps25990_unlock_writes(uint8_t addr);
bool tps25990_lock_writes(uint8_t addr);
bool tps25990_read_device_config(uint8_t addr, uint16_t *out);
bool tps25990_write_device_config(uint8_t addr, uint16_t value);
bool tps25990_read_retry_config(uint8_t addr, uint8_t *out);
bool tps25990_write_retry_config(uint8_t addr, uint8_t value);
bool tps25990_read_oc_timer(uint8_t addr, uint8_t *out);
bool tps25990_write_oc_timer(uint8_t addr, uint8_t value);
bool tps25990_read_viref(uint8_t addr, uint8_t *out);
bool tps25990_write_viref(uint8_t addr, uint8_t value);
bool tps25990_read_vin_uv_flt(uint8_t addr, uint16_t *out);
bool tps25990_write_vin_uv_flt(uint8_t addr, uint16_t value);
bool tps25990_read_vin_uv_warn(uint8_t addr, uint16_t *out);
bool tps25990_write_vin_uv_warn(uint8_t addr, uint16_t value);
bool tps25990_read_ot_warn(uint8_t addr, uint16_t *out);
bool tps25990_write_ot_warn(uint8_t addr, uint16_t value);
bool tps25990_read_status_temp(uint8_t addr, uint8_t *out);
bool tps25990_read_pk_min_avg(uint8_t addr, uint8_t *out);
bool tps25990_write_pk_min_avg(uint8_t addr, uint8_t value);

#endif /* TPS25990_H */
