/**
 * @file pdu.c
 * @brief Power Distribution Unit (PDU) implementation
 * 
 * Implements self-test and monitoring functions for 8 TPS25990 eFuses.
 */

#include "pdu.h"
#include "pdu_adc.h"
#include "pmbus.h"
#include "tps25990.h"
#include "linear11.h"
#include "definitions.h"

/* Per-eFuse telemetry CAN base ID (0x500-0x507) */
#define PDU_CAN_ID_EFUSE_BASE      0x500U
#define PDU_CAN_ID_MCU_TELEM        0x520U
#define PDU_CAN_STD_ID_SHIFT        18U
#define PDU_CAN_TX_WAIT_LOOPS       50000UL

/* MCU telemetry debug flags (byte1 in 0x520 frame) */
#define PDU_DBG_PMBUS_ENABLE_OK     (1U << 0)
#define PDU_DBG_TLM_ALL_READ_OK     (1U << 1)
#define PDU_DBG_ANY_READ_ERROR      (1U << 2)
#define PDU_DBG_ANY_PEC_ERROR       (1U << 3)
#define PDU_DBG_ANY_TIMEOUT         (1U << 4)
#define PDU_DBG_ANY_NACK_OR_BUS     (1U << 5)
#define PDU_DBG_ANY_ZERO_TELEM      (1U << 6)
#define PDU_DBG_ANY_CAN_TX_FAIL     (1U << 7)

/* MCU telemetry debug stage codes (byte4 in 0x520 frame) */
#define PDU_STAGE_INIT              1U
#define PDU_STAGE_RUNCHECKS         2U
#define PDU_STAGE_TELEMETRY         3U

/* TPS25990 PMBus I2C addresses for each eFuse channel */
static const uint8_t tps_addr[PDU_NUM_EFUSES] =
{
    0x45U,  /* Hybrid */
    0x48U,  /* Vent1 */
    0x43U,  /* Vent2 */
    0x40U,  /* IGN */
    0x51U,  /* Fuel */
    0x41U,  /* WP1 */
    0x46U,  /* WP2 */
    0x50U   /* 12V */
};

/* Minimum voltage threshold for voltage check (11.0V) */
#define MIN_VOLTAGE_THRESHOLD   11.0f

/* Power calculation tolerance (50% - very lenient for sanity check) */
#define POWER_CHECK_TOLERANCE   0.5f

/* Delay loop count for FET state change (~1ms at typical CPU speed) */
#define FET_STATE_DELAY_COUNT   10000UL

static uint8_t can1_msg_ram[CAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned(4)));
static uint8_t pdu_debug_flags = 0U;
static uint8_t pdu_debug_stage = PDU_STAGE_INIT;
static uint8_t pdu_last_error = 0U;
static uint8_t pdu_fail_channel = 0xFFU;
static uint8_t pdu_fail_command = 0U;

void PDU_CAN_Init(void)
{
    CAN1_MessageRAMConfigSet(can1_msg_ram);
}

static void pdu_enable_all_gpio_outputs(void)
{
    GPIO_HYBRID_OutputEnable();
    GPIO_VENT1_OutputEnable();
    GPIO_VENT2_OutputEnable();
    GPIO_IGNINJ_OutputEnable();
    GPIO_FUEL_P_OutputEnable();
    GPIO_WP1_OutputEnable();
    GPIO_WP2_OutputEnable();
    GPIO_EN12V_E_OutputEnable();

    GPIO_HYBRID_Set();
    GPIO_VENT1_Set();
    GPIO_VENT2_Set();
    GPIO_IGNINJ_Set();
    GPIO_FUEL_P_Set();
    GPIO_WP1_Set();
    GPIO_WP2_Set();
    GPIO_EN12V_E_Set();
}

static bool pdu_enable_all_pmbus_outputs(void)
{
    uint8_t i;

    for (i = 0U; i < PDU_NUM_EFUSES; i++)
    {
        if (pmbus_write_byte(tps_addr[i], PMBUS_CMD_OPERATION, PMBUS_OPERATION_ON) != PMBUS_OK) {
            return false;
        }
    }

    return true;
}

static bool pdu_can_recover_if_needed(void)
{
    CAN_ERROR err = CAN1_ErrorGet();

    if ((err & CAN_ERROR_BUS_OFF) != 0U)
    {
        CAN1_Initialize();
        CAN1_MessageRAMConfigSet(can1_msg_ram);
    }

    return true;
}

static uint32_t pdu_can_std_id_encode(uint16_t std_id)
{
    return ((uint32_t)(std_id & 0x7FFU)) << PDU_CAN_STD_ID_SHIFT;
}

static uint16_t pdu_float_to_u16_scaled(float value, float scale)
{
    float scaled = value * scale;

    if (scaled <= 0.0f) {
        return 0U;
    }
    if (scaled >= 65535.0f) {
        return 65535U;
    }

    return (uint16_t)scaled;
}

static bool pdu_can_send_efuse_frame(uint16_t id, uint16_t mv, uint16_t ma, uint16_t p_10mw, uint16_t status_word)
{
    CAN_TX_BUFFER tx = { 0 };
    uint32_t wait_count = 0UL;

    (void)pdu_can_recover_if_needed();

    while ((CAN1_TxFifoFreeLevelGet() == 0U) && (wait_count < PDU_CAN_TX_WAIT_LOOPS))
    {
        wait_count++;
    }

    if (CAN1_TxFifoFreeLevelGet() == 0U) {
        return false;
    }

    tx.id = pdu_can_std_id_encode(id);
    tx.rtr = 0U;
    tx.xtd = 0U;
    tx.esi = 0U;
    tx.dlc = 8U;
    tx.brs = 0U;
    tx.fdf = 0U;
    tx.efc = 0U;
    tx.mm = 0U;

    tx.data[0] = (uint8_t)(mv & 0xFFU);
    tx.data[1] = (uint8_t)((mv >> 8) & 0xFFU);
    tx.data[2] = (uint8_t)(ma & 0xFFU);
    tx.data[3] = (uint8_t)((ma >> 8) & 0xFFU);
    tx.data[4] = (uint8_t)(p_10mw & 0xFFU);
    tx.data[5] = (uint8_t)((p_10mw >> 8) & 0xFFU);
    tx.data[6] = (uint8_t)(status_word & 0xFFU);
    tx.data[7] = (uint8_t)((status_word >> 8) & 0xFFU);

    return CAN1_MessageTransmitFifo(1U, &tx);
}

static bool pdu_can_send_mcu_frame(
    uint8_t flt_bitmap,
    uint8_t system_flags,
    uint16_t shunt_ma,
    uint8_t dbg_stage,
    uint8_t dbg_error,
    uint8_t dbg_fail_channel,
    uint8_t dbg_fail_command)
{
    CAN_TX_BUFFER tx = { 0 };
    uint32_t wait_count = 0UL;

    (void)pdu_can_recover_if_needed();

    while ((CAN1_TxFifoFreeLevelGet() == 0U) && (wait_count < PDU_CAN_TX_WAIT_LOOPS))
    {
        wait_count++;
    }

    if (CAN1_TxFifoFreeLevelGet() == 0U) {
        return false;
    }

    tx.id = pdu_can_std_id_encode(PDU_CAN_ID_MCU_TELEM);
    tx.rtr = 0U;
    tx.xtd = 0U;
    tx.esi = 0U;
    tx.dlc = 8U;
    tx.brs = 0U;
    tx.fdf = 0U;
    tx.efc = 0U;
    tx.mm = 0U;

    tx.data[0] = flt_bitmap;
    tx.data[1] = system_flags;
    tx.data[2] = (uint8_t)(shunt_ma & 0xFFU);
    tx.data[3] = (uint8_t)((shunt_ma >> 8) & 0xFFU);
    tx.data[4] = dbg_stage;
    tx.data[5] = dbg_error;
    tx.data[6] = dbg_fail_channel;
    tx.data[7] = dbg_fail_command;

    return CAN1_MessageTransmitFifo(1U, &tx);
}

/**
 * @brief Software delay using busy-wait loop
 * 
 * Note: This is a simple busy-wait delay. For production code, consider
 * using SYSTICK_DelayMs() or other timer-based delays for better CPU utilization.
 * 
 * @param count Number of iterations to delay
 */
static void delay_loop(uint32_t count)
{
    volatile uint32_t i;
    for (i = 0U; i < count; i++) {
        /* Busy wait - prevents compiler optimization */
    }
}

static uint8_t pdu_pmbus_status_to_error_code(pmbus_status_t st)
{
    switch (st)
    {
        case PMBUS_OK:
            return 0U;
        case PMBUS_NACK:
            return 1U;
        case PMBUS_TIMEOUT:
            return 2U;
        case PMBUS_PEC_ERROR:
            return 3U;
        case PMBUS_BUS_ERROR:
            return 4U;
        default:
            return 15U;
    }
}

static void pdu_note_pmbus_error(pmbus_status_t st, uint8_t channel, uint8_t command)
{
    pdu_debug_flags |= PDU_DBG_ANY_READ_ERROR;
    pdu_last_error = pdu_pmbus_status_to_error_code(st);
    pdu_fail_channel = channel;
    pdu_fail_command = command;

    if (st == PMBUS_PEC_ERROR)
    {
        pdu_debug_flags |= PDU_DBG_ANY_PEC_ERROR;
    }
    else if (st == PMBUS_TIMEOUT)
    {
        pdu_debug_flags |= PDU_DBG_ANY_TIMEOUT;
    }
    else if ((st == PMBUS_NACK) || (st == PMBUS_BUS_ERROR))
    {
        pdu_debug_flags |= PDU_DBG_ANY_NACK_OR_BUS;
    }
}

/**
 * @brief Check if all eFuses have input voltage above threshold
 * 
 * Reads VOUT from each eFuse and verifies it's above 11V.
 * 
 * @return true if all voltages are OK, false if any is below threshold
 */
static bool check_voltage_all(void)
{
    uint8_t i;
    
    for (i = 0U; i < PDU_NUM_EFUSES; i++)
    {
        uint16_t raw;
        
        if (pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_VOUT, &raw) != PMBUS_OK) {
            return false;
        }

        float v = linear11_to_float(raw);
        if (v < MIN_VOLTAGE_THRESHOLD) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Check power calculation consistency for all eFuses
 * 
 * Compares calculated power (V*I) with measured power from each eFuse.
 * 
 * @return true if all power readings are consistent, false otherwise
 */
static bool check_power_all(void)
{
    uint8_t i;
    
    for (i = 0U; i < PDU_NUM_EFUSES; i++)
    {
        uint16_t vraw, iraw, praw;

        if (pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_VOUT, &vraw) != PMBUS_OK) {
            return false;
        }
        if (pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_IIN, &iraw) != PMBUS_OK) {
            return false;
        }
        if (pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_PIN, &praw) != PMBUS_OK) {
            return false;
        }

        float v = linear11_to_float(vraw);
        float current = linear11_to_float(iraw);
        float p_calc = v * current;
        float p_meas = linear11_to_float(praw);

        /* Skip check if power is very low (avoid division issues) */
        if (p_calc < 0.1f) {
            continue;
        }

        /* Check if measured power is at least 50% of calculated */
        if (p_meas < (p_calc * POWER_CHECK_TOLERANCE)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Check FET driver operation for all eFuses
 * 
 * For each eFuse:
 * 1. Turn OFF the output
 * 2. Turn ON the output
 * 3. Verify FET_OFF status bit changes correctly
 * 
 * @return true if all FET drivers respond correctly, false otherwise
 */
static bool check_fet_all(void)
{
    uint8_t i;
    
    for (i = 0U; i < PDU_NUM_EFUSES; i++)
    {
        uint8_t status;

        /* Turn OFF the output */
        if (pmbus_write_byte(tps_addr[i], PMBUS_CMD_OPERATION, PMBUS_OPERATION_OFF) != PMBUS_OK) {
            return false;
        }

        /* Delay for FET state change */
        delay_loop(FET_STATE_DELAY_COUNT);

        /* Read STATUS_BYTE to verify FET is OFF */
        if (pmbus_read_byte(tps_addr[i], PMBUS_CMD_STATUS_BYTE, &status) != PMBUS_OK) {
            return false;
        }

        /* Verify FET_OFF bit is SET (FET should be off) */
        if ((status & TPS25990_SB_FET_OFF) == 0U) {
            return false;  /* FET should be off but isn't */
        }

        /* Turn ON the output */
        if (pmbus_write_byte(tps_addr[i], PMBUS_CMD_OPERATION, PMBUS_OPERATION_ON) != PMBUS_OK) {
            return false;
        }

        /* Delay for FET state change */
        delay_loop(FET_STATE_DELAY_COUNT);

        /* Read STATUS_BYTE to verify FET is ON */
        if (pmbus_read_byte(tps_addr[i], PMBUS_CMD_STATUS_BYTE, &status) != PMBUS_OK) {
            return false;
        }

        /* Verify FET_OFF bit is CLEAR (FET should be on) */
        if ((status & TPS25990_SB_FET_OFF) != 0U) {
            return false;  /* FET should be on but isn't */
        }
    }
    return true;
}

void PDU_Init(void)
{
    PDU_CAN_Init();

    /* Initialize ADC for IMON readings */
    PDU_ADC_Init();

    /* Force-enable all GPIO output enable pins (active-high) */
    pdu_enable_all_gpio_outputs();

    /* Configure LED GPIOs as outputs */
    GPIO_GLED_OutputEnable();
    GPIO_BLED_OutputEnable();
    GPIO_RLED_OutputEnable();

    /* LEDs are active-low, start with all OFF (Set = LED off) */
    GPIO_GLED_Set();
    GPIO_BLED_Set();
    GPIO_RLED_Set();

    pdu_debug_flags = 0U;
    pdu_debug_stage = PDU_STAGE_INIT;
    pdu_last_error = 0U;
    pdu_fail_channel = 0xFFU;
    pdu_fail_command = 0U;
}

void PDU_RunChecks(void)
{
    bool v_ok = check_voltage_all();
    bool p_ok = check_power_all();
    bool f_ok = check_fet_all();
    bool en_ok;

    pdu_debug_stage = PDU_STAGE_RUNCHECKS;

    pdu_enable_all_gpio_outputs();
    en_ok = pdu_enable_all_pmbus_outputs();
    if (!en_ok) {
        f_ok = false;
        pdu_debug_flags &= (uint8_t)(~PDU_DBG_PMBUS_ENABLE_OK);
        pdu_debug_flags |= PDU_DBG_ANY_READ_ERROR;
    } else {
        pdu_debug_flags |= PDU_DBG_PMBUS_ENABLE_OK;
    }

    /* 
     * Active-low LEDs:
     * - Clear() = LED ON (pulling low)
     * - Set() = LED OFF (pulling high)
     * - Toggle() = blink effect
     *
     * Green LED: Voltage check
     * Blue LED: Power calculation check
     * Red LED: FET driver check
     */
    
    /* Green LED - Voltage check */
    if (v_ok) {
        GPIO_GLED_Clear();  /* All OK - LED solid ON */
    } else {
        GPIO_GLED_Toggle(); /* Fault - LED blinks */
    }

    /* Blue LED - Power check */
    if (p_ok) {
        GPIO_BLED_Clear();  /* All OK - LED solid ON */
    } else {
        GPIO_BLED_Toggle(); /* Fault - LED blinks */
    }

    /* Red LED - FET check */
    if (f_ok) {
        GPIO_RLED_Clear();  /* All OK - LED solid ON */
    } else {
        GPIO_RLED_Toggle(); /* Fault - LED blinks */
    }
}

void PDU_PollAndSendTelemetry(void)
{
    uint8_t i;
    uint8_t flt_bitmap = 0U;
    uint16_t shunt_ma = 0U;
    bool all_reads_ok = true;

    pdu_debug_stage = PDU_STAGE_TELEMETRY;
    pdu_debug_flags &= (uint8_t)(~(PDU_DBG_TLM_ALL_READ_OK | PDU_DBG_ANY_ZERO_TELEM | PDU_DBG_ANY_CAN_TX_FAIL));
    pdu_fail_channel = 0xFFU;
    pdu_fail_command = 0U;

    for (i = 0U; i < PDU_NUM_EFUSES; i++)
    {
        uint16_t vraw = 0U;
        uint16_t iraw = 0U;
        uint16_t praw = 0U;
        uint16_t mv = 0U;
        uint16_t ma = 0U;
        uint16_t p_10mw = 0U;
        uint16_t status = 0xFFFFU;
        pmbus_status_t st;
        uint8_t failed_cmd = PMBUS_CMD_READ_VOUT;

        failed_cmd = PMBUS_CMD_READ_VOUT;
        st = pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_VOUT, &vraw);
        if (st == PMBUS_OK)
        {
            failed_cmd = PMBUS_CMD_READ_IIN;
            st = pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_IIN, &iraw);
        }
        if (st == PMBUS_OK)
        {
            failed_cmd = PMBUS_CMD_READ_PIN;
            st = pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_PIN, &praw);
        }
        if (st == PMBUS_OK)
        {
            failed_cmd = PMBUS_CMD_STATUS_WORD;
            st = pmbus_read_word(tps_addr[i], PMBUS_CMD_STATUS_WORD, &status);
        }

        if (st == PMBUS_OK)
        {
            mv = pdu_float_to_u16_scaled(linear11_to_float(vraw), 1000.0f);
            ma = pdu_float_to_u16_scaled(linear11_to_float(iraw), 1000.0f);
            p_10mw = pdu_float_to_u16_scaled(linear11_to_float(praw), 100.0f);

            if ((mv == 0U) && (ma == 0U) && (p_10mw == 0U)) {
                pdu_debug_flags |= PDU_DBG_ANY_ZERO_TELEM;
            }
        }
        else
        {
            all_reads_ok = false;
            pdu_note_pmbus_error(st, i, failed_cmd);
        }

        if (!pdu_can_send_efuse_frame((uint16_t)(PDU_CAN_ID_EFUSE_BASE + i), mv, ma, p_10mw, status)) {
            pdu_debug_flags |= PDU_DBG_ANY_CAN_TX_FAIL;
            pdu_last_error = 10U;
        }
    }

    if (all_reads_ok) {
        pdu_debug_flags |= PDU_DBG_TLM_ALL_READ_OK;
    } else {
        pdu_debug_flags &= (uint8_t)(~PDU_DBG_TLM_ALL_READ_OK);
    }

    /* FLT pins are active-low: HIGH = OK, LOW = fault */
    if (FLT_Get() == 0U) {
        flt_bitmap |= 0x01U;
    }
    if (FLTM_Get() == 0U) {
        flt_bitmap |= 0x02U;
    }

    if (!pdu_can_send_mcu_frame(
            flt_bitmap,
            pdu_debug_flags,
            shunt_ma,
            pdu_debug_stage,
            pdu_last_error,
            pdu_fail_channel,
            pdu_fail_command)) {
        pdu_debug_flags |= PDU_DBG_ANY_CAN_TX_FAIL;
        pdu_last_error = 10U;
    }
}