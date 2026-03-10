/**
 * @file pmbus.c
 * @brief PMBus/SMBus implementation for PIC32CM (SERCOM1 I2C)
 *
 * This implementation provides:
 * - PMBus send-byte, write-byte, write-word
 * - PMBus read-byte and read-word using repeated-start
 * - SMBus PEC generation and checking
 * - Transaction fault flags for diagnostics
 */

#include "pmbus.h"
#include "pmbus_pec.h"
#include "config/default/peripheral/sercom/i2c_master/plib_sercom1_i2c_master.h"

#define PMBUS_I2C_TIMEOUT_TICKS    (100000UL)
#define PMBUS_TRACE_QUEUE_SIZE      (24U)

static uint32_t g_pmbus_last_fault_flags = PMBUS_FAULT_NONE;
static uint8_t g_pmbus_last_sercom_error = (uint8_t)SERCOM_I2C_ERROR_NONE;
static pmbus_trace_t g_trace_queue[PMBUS_TRACE_QUEUE_SIZE];
static uint8_t g_trace_head = 0U;
static uint8_t g_trace_tail = 0U;
static uint8_t g_trace_count = 0U;
static uint8_t g_trace_seq = 0U;

static void pmbus_trace_push(const pmbus_trace_t *trace)
{
    if (trace == (const pmbus_trace_t *)0) {
        return;
    }

    g_trace_queue[g_trace_head] = *trace;
    g_trace_head = (uint8_t)((g_trace_head + 1U) % PMBUS_TRACE_QUEUE_SIZE);

    if (g_trace_count < PMBUS_TRACE_QUEUE_SIZE) {
        g_trace_count++;
    } else {
        g_trace_tail = (uint8_t)((g_trace_tail + 1U) % PMBUS_TRACE_QUEUE_SIZE);
    }
}

bool pmbus_trace_pop(pmbus_trace_t *out)
{
    if ((out == (pmbus_trace_t *)0) || (g_trace_count == 0U)) {
        return false;
    }

    *out = g_trace_queue[g_trace_tail];
    g_trace_tail = (uint8_t)((g_trace_tail + 1U) % PMBUS_TRACE_QUEUE_SIZE);
    g_trace_count--;
    return true;
}

static void pmbus_set_fault(uint32_t flags)
{
    g_pmbus_last_fault_flags |= flags;
}

static void pmbus_begin_transaction(uint32_t op_flag)
{
    g_pmbus_last_fault_flags = PMBUS_FAULT_NONE;
    g_pmbus_last_sercom_error = (uint8_t)SERCOM_I2C_ERROR_NONE;
    pmbus_set_fault(op_flag);
}

uint8_t pmbus_get_last_sercom_error(void)
{
    return g_pmbus_last_sercom_error;
}

uint32_t pmbus_get_last_fault_flags(void)
{
    return g_pmbus_last_fault_flags;
}

void pmbus_clear_last_fault_flags(void)
{
    g_pmbus_last_fault_flags = PMBUS_FAULT_NONE;
}

static bool pmbus_wait_transfer_done(void)
{
    uint32_t timeout = PMBUS_I2C_TIMEOUT_TICKS;

    while (SERCOM1_I2C_IsBusy()) {
        if (timeout == 0UL) {
            pmbus_set_fault(PMBUS_FAULT_TIMEOUT);
            return false;
        }
        timeout--;
    }

    return true;
}

static pmbus_status_t pmbus_status_from_sercom_error(SERCOM_I2C_ERROR err)
{
    g_pmbus_last_sercom_error = (uint8_t)err;

    switch (err)
    {
        case SERCOM_I2C_ERROR_NONE:
            pmbus_set_fault(PMBUS_FAULT_ACK);
            return PMBUS_OK;

        case SERCOM_I2C_ERROR_NAK:
            pmbus_set_fault(PMBUS_FAULT_NACK);
            return PMBUS_NACK;

        case SERCOM_I2C_ERROR_BUS:
            pmbus_set_fault(PMBUS_FAULT_BUS_ERROR);
            return PMBUS_BUS_ERROR;

        default:
            pmbus_set_fault(PMBUS_FAULT_BUS_ERROR);
            return PMBUS_BUS_ERROR;
    }
}

static pmbus_status_t pmbus_finish_transfer(void)
{
    SERCOM_I2C_ERROR err;

    if (!pmbus_wait_transfer_done()) {
        SERCOM1_I2C_TransferAbort();
        return PMBUS_TIMEOUT;
    }

    err = SERCOM1_I2C_ErrorGet();
    return pmbus_status_from_sercom_error(err);
}

static bool pmbus_prepare_start(void)
{
    uint32_t timeout = PMBUS_I2C_TIMEOUT_TICKS;

    while (SERCOM1_I2C_IsBusy())
    {
        if (timeout == 0UL)
        {
            SERCOM1_I2C_TransferAbort();
            pmbus_set_fault(PMBUS_FAULT_START_ERROR | PMBUS_FAULT_TIMEOUT);
            return false;
        }
        timeout--;
    }

    return true;
}

static pmbus_status_t pmbus_start_write(uint8_t addr, uint8_t *tx, uint32_t len)
{
    if (!pmbus_prepare_start()) {
        return PMBUS_TIMEOUT;
    }

    if (!SERCOM1_I2C_Write(addr, tx, len)) {
        pmbus_set_fault(PMBUS_FAULT_START_ERROR);
        return PMBUS_BUS_ERROR;
    }

    return pmbus_finish_transfer();
}

static pmbus_status_t pmbus_start_write_read(uint8_t addr,
                                             uint8_t *tx,
                                             uint32_t tx_len,
                                             uint8_t *rx,
                                             uint32_t rx_len)
{
    if (!pmbus_prepare_start()) {
        return PMBUS_TIMEOUT;
    }

    if (!SERCOM1_I2C_WriteRead(addr, tx, tx_len, rx, rx_len)) {
        pmbus_set_fault(PMBUS_FAULT_START_ERROR);
        return PMBUS_BUS_ERROR;
    }

    return pmbus_finish_transfer();
}

pmbus_status_t pmbus_send_byte(uint8_t addr, uint8_t command)
{
    uint8_t tx[2];
    uint8_t addr_w = (uint8_t)(addr << 1U);
    uint8_t crc = 0U;
    pmbus_status_t st;
    pmbus_trace_t trace = { 0 };

    pmbus_begin_transaction(PMBUS_FAULT_OP_WRITE);

    crc = pmbus_crc8_update(crc, addr_w);
    crc = pmbus_crc8_update(crc, command);

    tx[0] = command;
    tx[1] = crc;

    st = pmbus_start_write(addr, tx, 2U);

    trace.seq = ++g_trace_seq;
    trace.op = (uint8_t)PMBUS_TRACE_OP_SEND_BYTE;
    trace.addr = addr;
    trace.command = command;
    trace.status = (uint8_t)st;
    trace.fault_flags = g_pmbus_last_fault_flags;
    trace.tx_len = 2U;
    trace.tx[0] = tx[0];
    trace.tx[1] = tx[1];
    trace.sercom_error = g_pmbus_last_sercom_error;
    trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
    pmbus_trace_push(&trace);

    return st;
}

pmbus_status_t pmbus_write_byte(uint8_t addr, uint8_t command, uint8_t data)
{
    uint8_t tx[3];
    uint8_t addr_w = (uint8_t)(addr << 1U);
    uint8_t crc = 0U;
    pmbus_status_t st;
    pmbus_trace_t trace = { 0 };

    pmbus_begin_transaction(PMBUS_FAULT_OP_WRITE);

    crc = pmbus_crc8_update(crc, addr_w);
    crc = pmbus_crc8_update(crc, command);
    crc = pmbus_crc8_update(crc, data);

    tx[0] = command;
    tx[1] = data;
    tx[2] = crc;

    st = pmbus_start_write(addr, tx, 3U);

    trace.seq = ++g_trace_seq;
    trace.op = (uint8_t)PMBUS_TRACE_OP_WRITE_BYTE;
    trace.addr = addr;
    trace.command = command;
    trace.status = (uint8_t)st;
    trace.fault_flags = g_pmbus_last_fault_flags;
    trace.tx_len = 3U;
    trace.tx[0] = tx[0];
    trace.tx[1] = tx[1];
    trace.tx[2] = tx[2];
    trace.sercom_error = g_pmbus_last_sercom_error;
    trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
    pmbus_trace_push(&trace);

    return st;
}

pmbus_status_t pmbus_write_word(uint8_t addr, uint8_t command, uint16_t data)
{
    uint8_t tx[4];
    uint8_t data_lo = (uint8_t)(data & 0xFFU);
    uint8_t data_hi = (uint8_t)((data >> 8U) & 0xFFU);
    uint8_t addr_w = (uint8_t)(addr << 1U);
    uint8_t crc = 0U;
    pmbus_status_t st;
    pmbus_trace_t trace = { 0 };

    pmbus_begin_transaction(PMBUS_FAULT_OP_WRITE);

    crc = pmbus_crc8_update(crc, addr_w);
    crc = pmbus_crc8_update(crc, command);
    crc = pmbus_crc8_update(crc, data_lo);
    crc = pmbus_crc8_update(crc, data_hi);

    tx[0] = command;
    tx[1] = data_lo;
    tx[2] = data_hi;
    tx[3] = crc;

    st = pmbus_start_write(addr, tx, 4U);

    trace.seq = ++g_trace_seq;
    trace.op = (uint8_t)PMBUS_TRACE_OP_WRITE_WORD;
    trace.addr = addr;
    trace.command = command;
    trace.status = (uint8_t)st;
    trace.fault_flags = g_pmbus_last_fault_flags;
    trace.tx_len = 4U;
    trace.tx[0] = tx[0];
    trace.tx[1] = tx[1];
    trace.tx[2] = tx[2];
    trace.tx[3] = tx[3];
    trace.sercom_error = g_pmbus_last_sercom_error;
    trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
    pmbus_trace_push(&trace);

    return st;
}

pmbus_status_t pmbus_read_byte(uint8_t addr, uint8_t command, uint8_t *out)
{
    uint8_t rx[2];
    uint8_t cmd = command;
    uint8_t addr_w = (uint8_t)(addr << 1U);
    uint8_t addr_r = (uint8_t)((addr << 1U) | 1U);
    uint8_t calc_pec = 0U;
    pmbus_status_t st;
    pmbus_trace_t trace = { 0 };

    pmbus_begin_transaction(PMBUS_FAULT_OP_READ);

    if (out == (uint8_t *)0) {
        pmbus_set_fault(PMBUS_FAULT_PARAM_ERROR);
        st = PMBUS_BUS_ERROR;
        trace.seq = ++g_trace_seq;
        trace.op = (uint8_t)PMBUS_TRACE_OP_READ_BYTE;
        trace.addr = addr;
        trace.command = command;
        trace.status = (uint8_t)st;
        trace.fault_flags = g_pmbus_last_fault_flags;
        trace.tx_len = 1U;
        trace.tx[0] = command;
        trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
        pmbus_trace_push(&trace);
        return st;
    }

    st = pmbus_start_write_read(addr, &cmd, 1U, rx, sizeof(rx));
    if (st != PMBUS_OK) {
        trace.seq = ++g_trace_seq;
        trace.op = (uint8_t)PMBUS_TRACE_OP_READ_BYTE;
        trace.addr = addr;
        trace.command = command;
        trace.status = (uint8_t)st;
        trace.fault_flags = g_pmbus_last_fault_flags;
        trace.tx_len = 1U;
        trace.tx[0] = command;
        trace.sercom_error = g_pmbus_last_sercom_error;
        trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
        pmbus_trace_push(&trace);
        return st;
    }

    calc_pec = pmbus_crc8_update(calc_pec, addr_w);
    calc_pec = pmbus_crc8_update(calc_pec, command);
    calc_pec = pmbus_crc8_update(calc_pec, addr_r);
    calc_pec = pmbus_crc8_update(calc_pec, rx[0]);

    if (calc_pec != rx[1]) {
        pmbus_set_fault(PMBUS_FAULT_PEC_ERROR);
        st = PMBUS_PEC_ERROR;
        trace.seq = ++g_trace_seq;
        trace.op = (uint8_t)PMBUS_TRACE_OP_READ_BYTE;
        trace.addr = addr;
        trace.command = command;
        trace.status = (uint8_t)st;
        trace.fault_flags = g_pmbus_last_fault_flags;
        trace.tx_len = 1U;
        trace.rx_len = 2U;
        trace.tx[0] = command;
        trace.rx[0] = rx[0];
        trace.rx[1] = rx[1];
        trace.pec_calc = calc_pec;
        trace.pec_rx = rx[1];
        trace.sercom_error = g_pmbus_last_sercom_error;
        trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
        pmbus_trace_push(&trace);
        return st;
    }

    *out = rx[0];
    st = PMBUS_OK;
    trace.seq = ++g_trace_seq;
    trace.op = (uint8_t)PMBUS_TRACE_OP_READ_BYTE;
    trace.addr = addr;
    trace.command = command;
    trace.status = (uint8_t)st;
    trace.fault_flags = g_pmbus_last_fault_flags;
    trace.tx_len = 1U;
    trace.rx_len = 2U;
    trace.tx[0] = command;
    trace.rx[0] = rx[0];
    trace.rx[1] = rx[1];
    trace.pec_calc = calc_pec;
    trace.pec_rx = rx[1];
    trace.sercom_error = g_pmbus_last_sercom_error;
    trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
    pmbus_trace_push(&trace);
    return st;
}

pmbus_status_t pmbus_read_word(uint8_t addr, uint8_t command, uint16_t *out)
{
    uint8_t rx[3];
    uint8_t cmd = command;
    uint8_t addr_w = (uint8_t)(addr << 1U);
    uint8_t addr_r = (uint8_t)((addr << 1U) | 1U);
    uint8_t calc_pec = 0U;
    pmbus_status_t st;
    pmbus_trace_t trace = { 0 };

    pmbus_begin_transaction(PMBUS_FAULT_OP_READ);

    if (out == (uint16_t *)0) {
        pmbus_set_fault(PMBUS_FAULT_PARAM_ERROR);
        st = PMBUS_BUS_ERROR;
        trace.seq = ++g_trace_seq;
        trace.op = (uint8_t)PMBUS_TRACE_OP_READ_WORD;
        trace.addr = addr;
        trace.command = command;
        trace.status = (uint8_t)st;
        trace.fault_flags = g_pmbus_last_fault_flags;
        trace.tx_len = 1U;
        trace.tx[0] = command;
        trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
        pmbus_trace_push(&trace);
        return st;
    }

    st = pmbus_start_write_read(addr, &cmd, 1U, rx, sizeof(rx));
    if (st != PMBUS_OK) {
        trace.seq = ++g_trace_seq;
        trace.op = (uint8_t)PMBUS_TRACE_OP_READ_WORD;
        trace.addr = addr;
        trace.command = command;
        trace.status = (uint8_t)st;
        trace.fault_flags = g_pmbus_last_fault_flags;
        trace.tx_len = 1U;
        trace.tx[0] = command;
        trace.sercom_error = g_pmbus_last_sercom_error;
        trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
        pmbus_trace_push(&trace);
        return st;
    }

    calc_pec = pmbus_crc8_update(calc_pec, addr_w);
    calc_pec = pmbus_crc8_update(calc_pec, command);
    calc_pec = pmbus_crc8_update(calc_pec, addr_r);
    calc_pec = pmbus_crc8_update(calc_pec, rx[0]);
    calc_pec = pmbus_crc8_update(calc_pec, rx[1]);

    if (calc_pec != rx[2]) {
        pmbus_set_fault(PMBUS_FAULT_PEC_ERROR);
        st = PMBUS_PEC_ERROR;
        trace.seq = ++g_trace_seq;
        trace.op = (uint8_t)PMBUS_TRACE_OP_READ_WORD;
        trace.addr = addr;
        trace.command = command;
        trace.status = (uint8_t)st;
        trace.fault_flags = g_pmbus_last_fault_flags;
        trace.tx_len = 1U;
        trace.rx_len = 3U;
        trace.tx[0] = command;
        trace.rx[0] = rx[0];
        trace.rx[1] = rx[1];
        trace.rx[2] = rx[2];
        trace.pec_calc = calc_pec;
        trace.pec_rx = rx[2];
        trace.sercom_error = g_pmbus_last_sercom_error;
        trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
        pmbus_trace_push(&trace);
        return st;
    }

    *out = (uint16_t)rx[0] | ((uint16_t)rx[1] << 8U);
    st = PMBUS_OK;
    trace.seq = ++g_trace_seq;
    trace.op = (uint8_t)PMBUS_TRACE_OP_READ_WORD;
    trace.addr = addr;
    trace.command = command;
    trace.status = (uint8_t)st;
    trace.fault_flags = g_pmbus_last_fault_flags;
    trace.tx_len = 1U;
    trace.rx_len = 3U;
    trace.tx[0] = command;
    trace.rx[0] = rx[0];
    trace.rx[1] = rx[1];
    trace.rx[2] = rx[2];
    trace.pec_calc = calc_pec;
    trace.pec_rx = rx[2];
    trace.sercom_error = g_pmbus_last_sercom_error;
    trace.trace_flags |= PMBUS_TRACE_FLAG_USED_PEC;
    pmbus_trace_push(&trace);
    return st;
}
