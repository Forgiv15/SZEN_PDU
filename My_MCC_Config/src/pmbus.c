#include "pmbus.h"
#include "pmbus_pec.h"
#include "peripheral/sercom/i2c_master/plib_sercom1_i2c_master.h"

#define I2C_TIMEOUT 100000UL

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

pmbus_status_t pmbus_write_byte(uint8_t addr, uint8_t command, uint8_t data)
{
    uint8_t tx[3];
    uint8_t crc = 0U;
    uint8_t addr_w = (uint8_t)((addr << 1U) | 0U);

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
    return SERCOM1_I2C_ErrorGet() ? PMBUS_NACK : PMBUS_OK;
}

pmbus_status_t pmbus_read_word(uint8_t addr, uint8_t command, uint16_t *out)
{
    uint8_t rx[3];
    uint8_t crc = 0U;
    uint8_t addr_w = (uint8_t)((addr << 1U) | 0U);
    uint8_t addr_r = (uint8_t)((addr << 1U) | 1U);

    if (!SERCOM1_I2C_Write(addr, &command, 1U)) {
        return PMBUS_BUS_ERROR;
    }
    if (!i2c_wait()) {
        return PMBUS_TIMEOUT;
    }

    if (!SERCOM1_I2C_Read(addr, rx, sizeof(rx))) {
        return PMBUS_BUS_ERROR;
    }
    if (!i2c_wait()) {
        return PMBUS_TIMEOUT;
    }

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
