#ifndef PMBUS_PEC_H
#define PMBUS_PEC_H

#include <stdint.h>

uint8_t pmbus_crc8_update(uint8_t crc, uint8_t data);
uint8_t pmbus_crc8_calc(const uint8_t *data, uint8_t len);

#endif /* PMBUS_PEC_H */
