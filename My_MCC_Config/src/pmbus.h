/**
 * @file pmbus.h
 * @brief PMBus/SMBus communication interface for TPS25990 eFuses
 * 
 * Provides I2C-based PMBus communication with PEC (Packet Error Checking)
 * support for the TPS25990 eFuse devices on PIC32CM5164JH01.
 */

#ifndef PMBUS_H
#define PMBUS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================
 * PMBus Standard Commands (from PMBus Specification)
 *===========================================================================*/

/* Standard PMBus Commands */
#define PMBUS_CMD_PAGE              0x00U
#define PMBUS_CMD_OPERATION         0x01U
#define PMBUS_CMD_ON_OFF_CONFIG     0x02U
#define PMBUS_CMD_CLEAR_FAULTS      0x03U
#define PMBUS_CMD_WRITE_PROTECT     0x10U
#define PMBUS_CMD_CAPABILITY        0x19U
#define PMBUS_CMD_VOUT_MODE         0x20U

/* PMBus Threshold Configuration Commands */
#define PMBUS_CMD_VIN_OV_FLT        0x55U
#define PMBUS_CMD_VIN_UV_FLT        0x59U
#define PMBUS_CMD_IIN_OC_FLT        0x5BU
#define PMBUS_CMD_OT_FLT            0x5FU
#define PMBUS_CMD_OT_WARN           0x51U

/* PMBus Status Commands */
#define PMBUS_CMD_STATUS_BYTE       0x78U
#define PMBUS_CMD_STATUS_WORD       0x79U
#define PMBUS_CMD_STATUS_VOUT       0x7AU
#define PMBUS_CMD_STATUS_IOUT       0x7BU
#define PMBUS_CMD_STATUS_IN         0x7CU
#define PMBUS_CMD_STATUS_TEMP       0x7DU
#define PMBUS_CMD_STATUS_CML        0x7EU
#define PMBUS_CMD_STATUS_MFR        0x80U

/* PMBus Telemetry Read Commands */
#define PMBUS_CMD_READ_VIN          0x88U
#define PMBUS_CMD_READ_IIN          0x89U
#define PMBUS_CMD_READ_VOUT         0x8BU
#define PMBUS_CMD_READ_IOUT         0x8CU
#define PMBUS_CMD_READ_TEMP         0x8DU
#define PMBUS_CMD_READ_PIN          0x97U

/* PMBus Identification Commands */
#define PMBUS_CMD_PMBUS_REV         0x98U
#define PMBUS_CMD_MFR_ID            0x99U
#define PMBUS_CMD_MFR_MODEL         0x9AU
#define PMBUS_CMD_MFR_REVISION      0x9BU
#define PMBUS_CMD_IC_DEV_ID         0xADU
#define PMBUS_CMD_IC_DEV_REV        0xAEU

/*============================================================================
 * TPS25990-Specific Commands
 *===========================================================================*/

/* TPS25990 Manufacturer-Specific Status Registers */
#define TPS25990_CMD_STATUS_MFR_SPECIFIC_2  0xF3U

/* TPS25990 Configuration Commands */
#define TPS25990_CMD_DEVICE_CONFIG      0xE4U
#define TPS25990_CMD_ADC_CONFIG         0xE7U
#define TPS25990_CMD_RETRY_CONFIG       0xE7U
#define TPS25990_CMD_ADC_CONFIG_2       0xE9U
#define TPS25990_CMD_ALERT_MASK         0xDBU

/* TPS25990 Telemetry Read Commands */
#define TPS25990_CMD_READ_AUX           0xEBU
#define TPS25990_CMD_READ_EIN           0x86U
#define TPS25990_CMD_READ_VBB           0xE3U

/* TPS25990 Protection Configuration */
#define TPS25990_CMD_IREF_DAC           0xE5U
#define TPS25990_CMD_OC_TIMER           0xE6U
#define TPS25990_CMD_PEAK_POWER         0xEDU

/* TPS25990 Blackbox Commands */
#define TPS25990_CMD_READ_BB_EEPROM     0xF4U
#define TPS25990_CMD_BB_HEADER          0xBAU
#define TPS25990_CMD_BB_COUNT           0xBBU

/* TPS25990 Manufacturer Write Protect */
#define TPS25990_CMD_MFR_WRITE_PROTECT  0xF8U

/*============================================================================
 * PMBus OPERATION Command Bit Definitions
 *===========================================================================*/

#define PMBUS_OPERATION_OFF         0x00U   /* Output OFF (immediate) */
#define PMBUS_OPERATION_ON          0x80U   /* Output ON */
#define PMBUS_OPERATION_MARGIN_LOW  0x98U   /* Margin Low */
#define PMBUS_OPERATION_MARGIN_HIGH 0xA8U   /* Margin High */

/*============================================================================
 * PMBus Status Return Type
 *===========================================================================*/

typedef enum {
    PMBUS_OK = 0,           /**< Operation completed successfully */
    PMBUS_NACK,             /**< Device did not acknowledge */
    PMBUS_TIMEOUT,          /**< Communication timeout */
    PMBUS_PEC_ERROR,        /**< PEC (CRC) check failed */
    PMBUS_BUS_ERROR         /**< I2C bus error */
} pmbus_status_t;

/*============================================================================
 * PMBus Fault Flags (last transaction)
 *===========================================================================*/

#define PMBUS_FAULT_NONE          (0UL)
#define PMBUS_FAULT_OP_READ       (1UL << 0)
#define PMBUS_FAULT_OP_WRITE      (1UL << 1)
#define PMBUS_FAULT_ACK           (1UL << 2)
#define PMBUS_FAULT_NACK          (1UL << 3)
#define PMBUS_FAULT_TIMEOUT       (1UL << 4)
#define PMBUS_FAULT_PEC_ERROR     (1UL << 5)
#define PMBUS_FAULT_BUS_ERROR     (1UL << 6)
#define PMBUS_FAULT_PARAM_ERROR   (1UL << 7)
#define PMBUS_FAULT_START_ERROR   (1UL << 8)

#define PMBUS_TRACE_FLAG_USED_PEC       (1U << 0)

/*============================================================================
 * PMBus Transaction Trace
 *===========================================================================*/

typedef enum {
    PMBUS_TRACE_OP_NONE = 0,
    PMBUS_TRACE_OP_SEND_BYTE,
    PMBUS_TRACE_OP_WRITE_BYTE,
    PMBUS_TRACE_OP_WRITE_WORD,
    PMBUS_TRACE_OP_READ_BYTE,
    PMBUS_TRACE_OP_READ_WORD
} pmbus_trace_op_t;

typedef struct {
    uint8_t seq;
    uint8_t op;
    uint8_t addr;
    uint8_t command;
    uint8_t status;
    uint32_t fault_flags;
    uint8_t tx_len;
    uint8_t rx_len;
    uint8_t tx[4];
    uint8_t rx[3];
    uint8_t pec_calc;
    uint8_t pec_rx;
    uint8_t sercom_error;
    uint8_t trace_flags;
} pmbus_trace_t;

/*============================================================================
 * PMBus Function Declarations
 *===========================================================================*/

/**
 * @brief Write a single byte via PMBus with PEC
 * 
 * @param addr 7-bit I2C device address
 * @param command PMBus command byte
 * @param data Byte to write
 * @return pmbus_status_t PMBUS_OK on success
 */
pmbus_status_t pmbus_write_byte(uint8_t addr, uint8_t command, uint8_t data);

/**
 * @brief Write a 16-bit word via PMBus with PEC
 * 
 * @param addr 7-bit I2C device address
 * @param command PMBus command byte
 * @param data 16-bit word to write (little-endian)
 * @return pmbus_status_t PMBUS_OK on success
 */
pmbus_status_t pmbus_write_word(uint8_t addr, uint8_t command, uint16_t data);

/**
 * @brief Read a single byte via PMBus with PEC verification
 * 
 * @param addr 7-bit I2C device address
 * @param command PMBus command byte
 * @param out Pointer to store read byte
 * @return pmbus_status_t PMBUS_OK on success
 */
pmbus_status_t pmbus_read_byte(uint8_t addr, uint8_t command, uint8_t *out);

/**
 * @brief Read a 16-bit word via PMBus with PEC verification
 * 
 * @param addr 7-bit I2C device address
 * @param command PMBus command byte
 * @param out Pointer to store read word (little-endian)
 * @return pmbus_status_t PMBUS_OK on success
 */
pmbus_status_t pmbus_read_word(uint8_t addr, uint8_t command, uint16_t *out);

/**
 * @brief Send a command without data (Send Byte operation)
 * 
 * @param addr 7-bit I2C device address
 * @param command PMBus command byte
 * @return pmbus_status_t PMBUS_OK on success
 */
pmbus_status_t pmbus_send_byte(uint8_t addr, uint8_t command);

uint8_t pmbus_get_last_sercom_error(void);

/**
 * @brief Get bitwise fault flags of the most recent PMBus transaction
 */
uint32_t pmbus_get_last_fault_flags(void);

/**
 * @brief Clear stored PMBus transaction fault flags
 */
void pmbus_clear_last_fault_flags(void);

/**
 * @brief Pop oldest PMBus transaction trace record from internal queue
 *
 * @param out Pointer to record destination
 * @return true if a record was popped, false if queue is empty
 */
bool pmbus_trace_pop(pmbus_trace_t *out);

#ifdef __cplusplus
}
#endif

#endif /* PMBUS_H */