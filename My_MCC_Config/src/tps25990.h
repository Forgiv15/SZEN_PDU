#ifndef TPS25990_H
#define TPS25990_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    /* raw PMBus words */
    uint16_t status_word;
    uint16_t vin_raw;
    uint16_t vout_raw;
    uint16_t iin_raw;
    uint16_t pin_raw;
    uint16_t temp_raw;

    /* decoded values (SI units) */
    float vin_V;
    float vout_V;
    float iin_A;
    float pin_W;
    float temp_C;

    /* sanity */
    bool power_mismatch;
} tps25990_data_t;

bool tps25990_read_all(uint8_t addr, tps25990_data_t *out);

#endif /* TPS25990_H */
