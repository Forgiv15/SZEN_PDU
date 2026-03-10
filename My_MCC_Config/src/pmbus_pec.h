/**
 * @file pmbus_pec.h
 * @brief SMBus PEC (CRC-8) helpers for PMBus transactions
 */

#ifndef PMBUS_PEC_H
#define PMBUS_PEC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SMBus CRC-8 polynomial: x^8 + x^2 + x + 1 (0x07), init=0x00 */
uint8_t pmbus_crc8_update(uint8_t crc, uint8_t data);
uint8_t pmbus_crc8(const uint8_t *data, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif /* PMBUS_PEC_H */