/**
 * @file pmbus.c
 * @brief PMBus/SMBus implementation with PEC for PIC32CM5164JH01
 * 
 * Implements PMBus read/write operations using the SERCOM1 I2C peripheral
 * with full PEC (Packet Error Checking) support as per SMBus specification.
 */

#include "pmbus.h"
#include "pmbus_pec.h"
#include "config/default/peripheral/sercom/i2c_master/plib_sercom1_i2c_master.h"

#define I2C_TIMEOUT 100000UL

/**
 * @brief Wait for I2C operation to complete with timeout
 * @return true if completed, false if timeout
 */
static bool i2c_wait(void)
{
    uint32_t t = I2C_TIMEOUT;
    while (SERCOM1_I2C_IsBusy()) {
        if (t-- == 0UL) {
            return false;
        }
    }
    return true;
}

pmbus_status_t pmbus_send_byte(uint8_t addr, uint8_t command)
{
    uint8_t tx[2];
    uint8_t crc = 0U;
    uint8_t addr_w = (uint8_t)(addr << 1U);  /* Write address = 7-bit addr shifted left */

    /* Calculate PEC over: slave address (write) + command */
    crc = pmbus_crc8_update(crc, addr_w);
    crc = pmbus_crc8_update(crc, command);

    tx[0] = command;
    tx[1] = crc;

    if (!SERCOM1_I2C_Write(addr, tx, sizeof(tx))) {
        return PMBUS_BUS_ERROR;
    }
    if (!i2c_wait()) {
        return PMBUS_TIMEOUT;
    }
    return SERCOM1_I2C_ErrorGet() != SERCOM_I2C_ERROR_NONE ? PMBUS_NACK : PMBUS_OK;
}

pmbus_status_t pmbus_write_byte(uint8_t addr, uint8_t command, uint8_t data)
{
    uint8_t tx[3];
    uint8_t crc = 0U;
    uint8_t addr_w = (uint8_t)(addr << 1U);  /* Write address = 7-bit addr shifted left */

    /* Calculate PEC over: slave address (write) + command + data */
    crc = pmbus_crc8_update(crc, addr_w);
    crc = pmbus_crc8_update(crc, command);
    crc = pmbus_crc8_update(crc, data);

    tx[0] = command;
    tx[1] = data;
    tx[2] = crc;

    if (!SERCOM1_I2C_Write(addr, tx, sizeof(tx))) {
        return PMBUS_BUS_ERROR;
    }
    if (!i2c_wait()) {
        return PMBUS_TIMEOUT;
    }
    return SERCOM1_I2C_ErrorGet() != SERCOM_I2C_ERROR_NONE ? PMBUS_NACK : PMBUS_OK;
}

pmbus_status_t pmbus_write_word(uint8_t addr, uint8_t command, uint16_t data)
{
    uint8_t tx[4];
    uint8_t crc = 0U;
    uint8_t addr_w = (uint8_t)(addr << 1U);  /* Write address = 7-bit addr shifted left */
    uint8_t data_lo = (uint8_t)(data & 0xFFU);
    uint8_t data_hi = (uint8_t)((data >> 8U) & 0xFFU);

    /* Calculate PEC over: slave address (write) + command + data_lo + data_hi */
    crc = pmbus_crc8_update(crc, addr_w);
    crc = pmbus_crc8_update(crc, command);
    crc = pmbus_crc8_update(crc, data_lo);
    crc = pmbus_crc8_update(crc, data_hi);

    tx[0] = command;
    tx[1] = data_lo;
    tx[2] = data_hi;
    tx[3] = crc;

    if (!SERCOM1_I2C_Write(addr, tx, sizeof(tx))) {
        return PMBUS_BUS_ERROR;
    }
    if (!i2c_wait()) {
        return PMBUS_TIMEOUT;
    }
    return SERCOM1_I2C_ErrorGet() != SERCOM_I2C_ERROR_NONE ? PMBUS_NACK : PMBUS_OK;
}

pmbus_status_t pmbus_read_byte(uint8_t addr, uint8_t command, uint8_t *out)
{
    uint8_t rx[2];  /* data byte + PEC */
    uint8_t crc = 0U;
    uint8_t addr_w = (uint8_t)(addr << 1U);        /* Write address */
    uint8_t addr_r = (uint8_t)((addr << 1U) | 1U); /* Read address */

    /* Send command byte */
    if (!SERCOM1_I2C_Write(addr, &command, 1U)) {
        return PMBUS_BUS_ERROR;
    }
    if (!i2c_wait()) {
        return PMBUS_TIMEOUT;
    }
    if (SERCOM1_I2C_ErrorGet() != SERCOM_I2C_ERROR_NONE) {
        return PMBUS_NACK;
    }

    /* Read data byte + PEC */
    if (!SERCOM1_I2C_Read(addr, rx, sizeof(rx))) {
        return PMBUS_BUS_ERROR;
    }
    if (!i2c_wait()) {
        return PMBUS_TIMEOUT;
    }
    if (SERCOM1_I2C_ErrorGet() != SERCOM_I2C_ERROR_NONE) {
        return PMBUS_NACK;
    }

    /* Verify PEC: slave address (write) + command + slave address (read) + data */
    crc = pmbus_crc8_update(crc, addr_w);
    crc = pmbus_crc8_update(crc, command);
    crc = pmbus_crc8_update(crc, addr_r);
    crc = pmbus_crc8_update(crc, rx[0]);

    if (crc != rx[1]) {
        return PMBUS_PEC_ERROR;
    }

    *out = rx[0];
    return PMBUS_OK;
}

pmbus_status_t pmbus_read_word(uint8_t addr, uint8_t command, uint16_t *out)
{
    uint8_t rx[3];  /* data_lo + data_hi + PEC */
    uint8_t crc = 0U;
    uint8_t addr_w = (uint8_t)(addr << 1U);        /* Write address */
    uint8_t addr_r = (uint8_t)((addr << 1U) | 1U); /* Read address */

    /* Send command byte */
    if (!SERCOM1_I2C_Write(addr, &command, 1U)) {
        return PMBUS_BUS_ERROR;
    }
    if (!i2c_wait()) {
        return PMBUS_TIMEOUT;
    }
    if (SERCOM1_I2C_ErrorGet() != SERCOM_I2C_ERROR_NONE) {
        return PMBUS_NACK;
    }

    /* Read data word (2 bytes) + PEC */
    if (!SERCOM1_I2C_Read(addr, rx, sizeof(rx))) {
        return PMBUS_BUS_ERROR;
    }
    if (!i2c_wait()) {
        return PMBUS_TIMEOUT;
    }
    if (SERCOM1_I2C_ErrorGet() != SERCOM_I2C_ERROR_NONE) {
        return PMBUS_NACK;
    }

    /* Verify PEC: slave address (write) + command + slave address (read) + data_lo + data_hi */
    crc = pmbus_crc8_update(crc, addr_w);
    crc = pmbus_crc8_update(crc, command);
    crc = pmbus_crc8_update(crc, addr_r);
    crc = pmbus_crc8_update(crc, rx[0]);
    crc = pmbus_crc8_update(crc, rx[1]);

    if (crc != rx[2]) {
        return PMBUS_PEC_ERROR;
    }

    *out = (uint16_t)rx[0] | ((uint16_t)rx[1] << 8U);
    return PMBUS_OK;
}
