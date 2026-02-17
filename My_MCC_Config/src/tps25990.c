/**
 * @file tps25990.c
 * @brief TPS25990 eFuse driver implementation
 * 
 * Provides PMBus communication and status decoding for TPS25990 eFuse devices.
 */

#include "tps25990.h"
#include "pmbus.h"
#include "linear11.h"
#include <stddef.h>

/* Power calculation tolerance (15%) */
#define POWER_TOLERANCE 0.15f

/**
 * @brief Decode STATUS_BYTE from raw value
 */
static void decode_status_byte(uint8_t raw, tps25990_status_byte_t *out)
{
    out->busy        = (raw & TPS25990_SB_BUSY) != 0U;
    out->fet_off     = (raw & TPS25990_SB_FET_OFF) != 0U;
    out->vout_ov     = (raw & TPS25990_SB_VOUT_OV) != 0U;
    out->iout_oc     = (raw & TPS25990_SB_IOUT_OC) != 0U;
    out->vin_uv      = (raw & TPS25990_SB_VIN_UV) != 0U;
    out->temp_fault  = (raw & TPS25990_SB_TEMP) != 0U;
    out->cml_fault   = (raw & TPS25990_SB_CML) != 0U;
    out->other_fault = (raw & TPS25990_SB_NONE_ABOVE) != 0U;
}

/**
 * @brief Decode STATUS_IOUT from raw value
 */
static void decode_status_iout(uint8_t raw, tps25990_status_iout_t *out)
{
    out->oc_fault      = (raw & TPS25990_SIOUT_OC_FLT) != 0U;
    out->oc_lv_fault   = (raw & TPS25990_SIOUT_OC_LV_FLT) != 0U;
    out->oc_warning    = (raw & TPS25990_SIOUT_OC_WARN) != 0U;
    out->current_limit = (raw & TPS25990_SIOUT_CL) != 0U;
    out->pout_op_fault = (raw & TPS25990_SIOUT_POUT_OP_FLT) != 0U;
    out->pout_op_warn  = (raw & TPS25990_SIOUT_POUT_OP_WARN) != 0U;
}

/**
 * @brief Decode STATUS_TEMP from raw value
 */
static void decode_status_temp(uint8_t raw, tps25990_status_temp_t *out)
{
    out->ot_fault   = (raw & TPS25990_STEMP_OT_FLT) != 0U;
    out->ot_warning = (raw & TPS25990_STEMP_OT_WARN) != 0U;
}

/**
 * @brief Decode STATUS_IN from raw value
 */
static void decode_status_in(uint8_t raw, tps25990_status_in_t *out)
{
    out->vin_ov_fault = (raw & TPS25990_SIN_VIN_OV_FLT) != 0U;
    out->vin_ov_warn  = (raw & TPS25990_SIN_VIN_OV_WARN) != 0U;
    out->vin_uv_warn  = (raw & TPS25990_SIN_VIN_UV_WARN) != 0U;
    out->oc_fault     = (raw & TPS25990_SIN_OC_FLT) != 0U;
    out->vin_uv_fault = (raw & TPS25990_SIN_VIN_UV_FLT) != 0U;
}

/**
 * @brief Decode STATUS_CML from raw value
 */
static void decode_status_cml(uint8_t raw, tps25990_status_cml_t *out)
{
    out->inv_cmd    = (raw & TPS25990_SCML_INV_CMD) != 0U;
    out->inv_data   = (raw & TPS25990_SCML_INV_DATA) != 0U;
    out->pec_fail   = (raw & TPS25990_SCML_PEC_FAIL) != 0U;
    out->mem_fault  = (raw & TPS25990_SCML_MEM_FAULT) != 0U;
    out->proc_fault = (raw & TPS25990_SCML_PROC_FAULT) != 0U;
    out->comm_fault = (raw & TPS25990_SCML_COMM_FAULT) != 0U;
}

/**
 * @brief Decode STATUS_MFR_SPECIFIC from raw value
 */
static void decode_status_mfr(uint8_t raw, tps25990_status_mfr_t *out)
{
    out->short_fault = (raw & TPS25990_SMFR_SHORT_FLT) != 0U;
    out->hotswap     = (raw & TPS25990_SMFR_HOTSWAP) != 0U;
    out->fet_health  = (raw & TPS25990_SMFR_FET_HEALTH) != 0U;
}

bool tps25990_read_all(uint8_t addr, tps25990_data_t *d)
{
    if (d == NULL) {
        return false;
    }

    if (pmbus_read_word(addr, TPS25990_CMD_STATUS_WORD, &d->status_word) != PMBUS_OK) {
        return false;
    }
    if (pmbus_read_word(addr, TPS25990_CMD_READ_VIN, &d->vin_raw) != PMBUS_OK) {
        return false;
    }
    if (pmbus_read_word(addr, TPS25990_CMD_READ_VOUT, &d->vout_raw) != PMBUS_OK) {
        return false;
    }
    if (pmbus_read_word(addr, TPS25990_CMD_READ_IIN, &d->iin_raw) != PMBUS_OK) {
        return false;
    }
    if (pmbus_read_word(addr, TPS25990_CMD_READ_PIN, &d->pin_raw) != PMBUS_OK) {
        return false;
    }
    if (pmbus_read_word(addr, TPS25990_CMD_READ_TEMP, &d->temp_raw) != PMBUS_OK) {
        return false;
    }

    /* Convert Linear11 to float values */
    d->vin_V  = linear11_to_float(d->vin_raw);
    d->vout_V = linear11_to_float(d->vout_raw);
    d->iin_A  = linear11_to_float(d->iin_raw);
    d->pin_W  = linear11_to_float(d->pin_raw);
    d->temp_C = linear11_to_float(d->temp_raw);

    /* Sanity check: P ~= V * I */
    float expected = d->vin_V * d->iin_A;
    float diff = expected - d->pin_W;
    if (diff < 0.0f) {
        diff = -diff;
    }

    d->power_mismatch = (expected > 0.1f) &&
                        ((diff / expected) > POWER_TOLERANCE);

    return true;
}

bool tps25990_read_status_word(uint8_t addr, tps25990_status_word_t *out)
{
    uint16_t raw;
    
    if (out == NULL) {
        return false;
    }

    if (pmbus_read_word(addr, TPS25990_CMD_STATUS_WORD, &raw) != PMBUS_OK) {
        return false;
    }

    out->raw = raw;
    
    /* Decode high byte (bits 15:8) */
    out->vout_status  = (raw & TPS25990_STATUS_WORD_VOUT) != 0U;
    out->iout_status  = (raw & TPS25990_STATUS_WORD_IOUT) != 0U;
    out->input_status = (raw & TPS25990_STATUS_WORD_INPUT) != 0U;
    out->mfr_status   = (raw & TPS25990_STATUS_WORD_MFR) != 0U;
    out->pgoodb       = (raw & TPS25990_STATUS_WORD_PGOODB) != 0U;
    out->fet_off_hi   = (raw & TPS25990_STATUS_WORD_FET_OFF) != 0U;
    
    /* Decode low byte (STATUS_BYTE) */
    decode_status_byte((uint8_t)(raw & 0xFFU), &out->status_byte);
    
    return true;
}

bool tps25990_read_full_status(uint8_t addr, tps25990_full_status_t *out)
{
    uint16_t word_raw;
    uint8_t byte_raw;
    
    if (out == NULL) {
        return false;
    }

    /* Read STATUS_WORD (also contains STATUS_BYTE as low byte) */
    if (pmbus_read_word(addr, TPS25990_CMD_STATUS_WORD, &word_raw) != PMBUS_OK) {
        return false;
    }
    
    out->word.raw = word_raw;
    out->word.vout_status  = (word_raw & TPS25990_STATUS_WORD_VOUT) != 0U;
    out->word.iout_status  = (word_raw & TPS25990_STATUS_WORD_IOUT) != 0U;
    out->word.input_status = (word_raw & TPS25990_STATUS_WORD_INPUT) != 0U;
    out->word.mfr_status   = (word_raw & TPS25990_STATUS_WORD_MFR) != 0U;
    out->word.pgoodb       = (word_raw & TPS25990_STATUS_WORD_PGOODB) != 0U;
    out->word.fet_off_hi   = (word_raw & TPS25990_STATUS_WORD_FET_OFF) != 0U;
    decode_status_byte((uint8_t)(word_raw & 0xFFU), &out->word.status_byte);

    /* Read STATUS_IOUT */
    if (pmbus_read_byte(addr, TPS25990_CMD_STATUS_IOUT, &byte_raw) != PMBUS_OK) {
        return false;
    }
    decode_status_iout(byte_raw, &out->iout);

    /* Read STATUS_TEMP */
    if (pmbus_read_byte(addr, TPS25990_CMD_STATUS_TEMP, &byte_raw) != PMBUS_OK) {
        return false;
    }
    decode_status_temp(byte_raw, &out->temp);

    /* Read STATUS_IN */
    if (pmbus_read_byte(addr, TPS25990_CMD_STATUS_IN, &byte_raw) != PMBUS_OK) {
        return false;
    }
    decode_status_in(byte_raw, &out->input);

    /* Read STATUS_CML */
    if (pmbus_read_byte(addr, TPS25990_CMD_STATUS_CML, &byte_raw) != PMBUS_OK) {
        return false;
    }
    decode_status_cml(byte_raw, &out->cml);

    /* Read STATUS_MFR_SPECIFIC */
    if (pmbus_read_byte(addr, TPS25990_CMD_STATUS_MFR, &byte_raw) != PMBUS_OK) {
        return false;
    }
    decode_status_mfr(byte_raw, &out->mfr);

    return true;
}

bool tps25990_is_fet_on(uint8_t addr)
{
    uint8_t status_byte;
    
    if (pmbus_read_byte(addr, TPS25990_CMD_STATUS_BYTE, &status_byte) != PMBUS_OK) {
        return false;
    }
    
    /* FET is ON if FET_OFF bit is NOT set */
    return (status_byte & TPS25990_SB_FET_OFF) == 0U;
}

bool tps25990_turn_on(uint8_t addr)
{
    return pmbus_write_byte(addr, PMBUS_CMD_OPERATION, PMBUS_OPERATION_ON) == PMBUS_OK;
}

bool tps25990_turn_off(uint8_t addr)
{
    return pmbus_write_byte(addr, PMBUS_CMD_OPERATION, PMBUS_OPERATION_OFF) == PMBUS_OK;
}

bool tps25990_clear_faults(uint8_t addr)
{
    return pmbus_send_byte(addr, PMBUS_CMD_CLEAR_FAULTS) == PMBUS_OK;
}
