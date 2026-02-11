#ifndef PMBUS_H
#define PMBUS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    PMBUS_OK = 0,
    PMBUS_NACK,
    PMBUS_TIMEOUT,
    PMBUS_PEC_ERROR,
    PMBUS_BUS_ERROR
} pmbus_status_t;

pmbus_status_t pmbus_write_byte(uint8_t addr, uint8_t command, uint8_t data);
pmbus_status_t pmbus_read_word(uint8_t addr, uint8_t command, uint16_t *out);

#endif /* PMBUS_H */
