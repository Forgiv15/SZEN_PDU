#include "tps25990.h"
#include "pmbus.h"
#include "linear11.h"
#include "stddef.h"
#define CMD_STATUS_WORD 0x79U
#define CMD_READ_VIN    0x88U
#define CMD_READ_VOUT   0x8BU
#define CMD_READ_IIN    0x89U
#define CMD_READ_PIN    0x97U
#define CMD_READ_TEMP   0x8DU

#define POWER_TOLERANCE 0.15f  /* 15 %% allowed difference */

bool tps25990_read_all(uint8_t addr, tps25990_data_t *d)
{
    if (d == NULL) {
        return false;
    }

    if (pmbus_read_word(addr, CMD_STATUS_WORD, &d->status_word) != PMBUS_OK) return false;
    if (pmbus_read_word(addr, CMD_READ_VIN, &d->vin_raw) != PMBUS_OK) return false;
    if (pmbus_read_word(addr, CMD_READ_VOUT, &d->vout_raw) != PMBUS_OK) return false;
    if (pmbus_read_word(addr, CMD_READ_IIN, &d->iin_raw) != PMBUS_OK) return false;
    if (pmbus_read_word(addr, CMD_READ_PIN, &d->pin_raw) != PMBUS_OK) return false;
    if (pmbus_read_word(addr, CMD_READ_TEMP, &d->temp_raw) != PMBUS_OK) return false;

    d->vin_V  = linear11_to_float(d->vin_raw);
    d->vout_V = linear11_to_float(d->vout_raw);
    d->iin_A  = linear11_to_float(d->iin_raw);
    d->pin_W  = linear11_to_float(d->pin_raw);
    d->temp_C = linear11_to_float(d->temp_raw);

    /* sanity check: P ~= V * I */
    float expected = d->vin_V * d->iin_A;
    float diff = expected - d->pin_W;
    if (diff < 0.0f) diff = -diff;

    d->power_mismatch = (expected > 0.1f) &&
                        ((diff / expected) > POWER_TOLERANCE);

    return true;
}
