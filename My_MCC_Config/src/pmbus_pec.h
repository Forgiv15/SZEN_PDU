// My_MCC_Config/src/pmbus_pec.h

#ifndef PMBUS_PEC_H
#define PMBUS_PEC_H

#include <stdint.h>

/*******************************************************************************
 * PMBus PEC (Packet Error Checking) - CRC-8 per SMBus 2.0
 * Polynomial: x^8 + x^2 + x^1 + 1 = 0x07
 ******************************************************************************/

uint8_t pmbus_crc8_update(uint8_t crc, uint8_t data);
uint8_t pmbus_crc8(const uint8_t *data, uint8_t len);

#endif /* PMBUS_PEC_H */