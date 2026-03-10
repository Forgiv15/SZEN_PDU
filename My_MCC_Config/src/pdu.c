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
#include "definitions.h"

/* Per-eFuse telemetry CAN base ID (0x500-0x507) */
#define PDU_CAN_ID_EFUSE_BASE      0x500U
#define PDU_CAN_ID_ADC_BASE        0x510U
#define PDU_CAN_ID_MCU_TELEM        0x520U
#define PDU_CAN_ID_ERR_DETAIL_BASE  0x530U
#define PDU_CAN_ID_I2C_SCAN_BASE    0x540U
#define PDU_CAN_ID_PMBUS_DBG_META   0x560U
#define PDU_CAN_ID_PMBUS_DBG_DATA   0x561U
#define PDU_CAN_ID_PMBUS_DBG_EXT    0x562U
#define PDU_PMBUS_PEC_MODE_REQUIRED 0U
#define PDU_CAN_STD_ID_SHIFT        18U
#define PDU_CAN_TX_WAIT_LOOPS       50000UL

/* MCU telemetry active error bitmap (byte1 in 0x520 frame) */
#define PDU_ERR_ENABLE_FAIL          (1U << 0)
#define PDU_ERR_READ_FAIL            (1U << 1)
#define PDU_ERR_PEC_FAIL             (1U << 2)
#define PDU_ERR_TIMEOUT              (1U << 3)
#define PDU_ERR_NACK_OR_BUS          (1U << 4)
#define PDU_ERR_ZERO_TELEM           (1U << 5)
#define PDU_ERR_CAN_TX_FAIL          (1U << 6)
#define PDU_ERR_SCAN_NO_ACK          (1U << 7)

/* Telemetry poll period is 100ms, so 10 polls = 1 second error TTL */
#define PDU_ERROR_TTL_POLLS          10U

/* Detailed error record list settings */
#define PDU_ERROR_DETAIL_MAX         8U

#define PDU_I2C_SCAN_START_ADDR      0x40U
#define PDU_I2C_SCAN_END_ADDR        0x59U
#define PDU_I2C_SCAN_FRAME_COUNT     (((PDU_I2C_SCAN_END_ADDR - PDU_I2C_SCAN_START_ADDR + 1U) + 7U) / 8U)

/* Detailed error codes */
#define PDU_ERR_CODE_CAN_TX_FAIL     10U
#define PDU_ERR_CODE_ENABLE_FAIL     20U
#define PDU_ERR_CODE_SCAN_NO_ACK     21U
#define PDU_ERR_CODE_ADC_MISMATCH    30U

#define PDU_ADC_COMPARE_CMD          0xA0U
#define PDU_ADC_FLAG_VALID           (1U << 0)
#define PDU_ADC_FLAG_PMBUS_VALID     (1U << 1)
#define PDU_ADC_FLAG_MISMATCH        (1U << 2)
#define PDU_ADC_MISMATCH_MIN_A       0.25f
#define PDU_ADC_MISMATCH_MIN_DIFF_A  0.50f
#define PDU_ADC_MISMATCH_RATIO       0.25f

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

static const pdu_adc_channel_t pdu_adc_channels[PDU_NUM_EFUSES] =
{
    PDU_ADC_IMON_HYBRID,
    PDU_ADC_IMON_VENT1,
    PDU_ADC_IMON_VENT2,
    PDU_ADC_IMON_IGN,
    PDU_ADC_IMON_FUEL,
    PDU_ADC_IMON_WP1,
    PDU_ADC_IMON_WP2,
    PDU_ADC_IMON_12V
};

static const float pdu_r_imon_ohms[PDU_NUM_EFUSES] =
{
    390.0f,
    390.0f,
    390.0f,
    390.0f,
    560.0f,
    560.0f,
    560.0f,
    560.0f
};

static uint8_t can1_msg_ram[CAN1_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned(4)));
static uint8_t pdu_debug_flags = 0U;
static uint8_t pdu_debug_stage = PDU_STAGE_INIT;
static uint8_t pdu_last_error = 0U;
static uint8_t pdu_fail_channel = 0xFFU;
static uint8_t pdu_fail_command = 0U;
static uint8_t pdu_error_ttl[8] = { 0U };

typedef struct
{
    bool active;
    uint8_t err;
    uint8_t channel;
    uint8_t command;
    uint8_t ttl;
} pdu_error_detail_t;

static pdu_error_detail_t pdu_error_details[PDU_ERROR_DETAIL_MAX];
static uint8_t pdu_i2c_scan_masks[PDU_I2C_SCAN_FRAME_COUNT];
static uint8_t pdu_i2c_scan_found = 0U;
static uint8_t pdu_i2c_scan_masks_last[PDU_I2C_SCAN_FRAME_COUNT];
static uint8_t pdu_i2c_scan_found_last = 0xFFU;
static uint8_t pdu_i2c_scan_report_div = 0U;
static uint8_t pdu_i2c_scan_div = 0U;
static uint8_t pdu_comm_fail_streak = 0U;

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
    bool all_ok = true;

    for (i = 0U; i < PDU_NUM_EFUSES; i++)
    {
        if (pmbus_write_byte(tps_addr[i], PMBUS_CMD_OPERATION, PMBUS_OPERATION_ON) != PMBUS_OK) {
            all_ok = false;
        }
    }

    return all_ok;
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

static float pdu_absf(float value)
{
    return (value < 0.0f) ? -value : value;
}

static bool pdu_adc_current_mismatch(float pmbus_current_a, float adc_current_a, float *diff_out)
{
    float reference_current;
    float diff;
    float allowed_diff;

    diff = pdu_absf(pmbus_current_a - adc_current_a);
    reference_current = (pmbus_current_a > adc_current_a) ? pmbus_current_a : adc_current_a;
    allowed_diff = PDU_ADC_MISMATCH_MIN_DIFF_A;

    if ((reference_current * PDU_ADC_MISMATCH_RATIO) > allowed_diff)
    {
        allowed_diff = reference_current * PDU_ADC_MISMATCH_RATIO;
    }

    if (diff_out != NULL)
    {
        *diff_out = diff;
    }

    if (reference_current < PDU_ADC_MISMATCH_MIN_A)
    {
        return false;
    }

    return diff > allowed_diff;
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

static bool pdu_can_send_adc_frame(uint16_t id, uint16_t adc_ma, uint16_t adc_mv, uint16_t diff_ma, uint8_t flags)
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

    tx.data[0] = (uint8_t)(adc_ma & 0xFFU);
    tx.data[1] = (uint8_t)((adc_ma >> 8) & 0xFFU);
    tx.data[2] = (uint8_t)(adc_mv & 0xFFU);
    tx.data[3] = (uint8_t)((adc_mv >> 8) & 0xFFU);
    tx.data[4] = (uint8_t)(diff_ma & 0xFFU);
    tx.data[5] = (uint8_t)((diff_ma >> 8) & 0xFFU);
    tx.data[6] = flags;
    tx.data[7] = 0U;

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

static bool pdu_can_send_pmbus_dbg_meta_frame(const pmbus_trace_t *trace)
{
    CAN_TX_BUFFER tx = { 0 };
    uint32_t wait_count = 0UL;
    uint32_t flags;

    if (trace == NULL)
    {
        return false;
    }

    (void)pdu_can_recover_if_needed();

    while ((CAN1_TxFifoFreeLevelGet() == 0U) && (wait_count < PDU_CAN_TX_WAIT_LOOPS))
    {
        wait_count++;
    }

    if (CAN1_TxFifoFreeLevelGet() == 0U)
    {
        return false;
    }

    flags = trace->fault_flags;

    tx.id = pdu_can_std_id_encode(PDU_CAN_ID_PMBUS_DBG_META);
    tx.rtr = 0U;
    tx.xtd = 0U;
    tx.esi = 0U;
    tx.dlc = 8U;
    tx.brs = 0U;
    tx.fdf = 0U;
    tx.efc = 0U;
    tx.mm = 0U;

    tx.data[0] = trace->seq;
    tx.data[1] = trace->op;
    tx.data[2] = trace->addr;
    tx.data[3] = trace->command;
    tx.data[4] = trace->status;
    tx.data[5] = (uint8_t)(flags & 0xFFU);
    tx.data[6] = (uint8_t)((flags >> 8) & 0xFFU);
    tx.data[7] = trace->sercom_error;

    return CAN1_MessageTransmitFifo(1U, &tx);
}

static bool pdu_can_send_pmbus_dbg_data_frame(const pmbus_trace_t *trace)
{
    CAN_TX_BUFFER tx = { 0 };
    uint32_t wait_count = 0UL;

    if (trace == NULL)
    {
        return false;
    }

    (void)pdu_can_recover_if_needed();

    while ((CAN1_TxFifoFreeLevelGet() == 0U) && (wait_count < PDU_CAN_TX_WAIT_LOOPS))
    {
        wait_count++;
    }

    if (CAN1_TxFifoFreeLevelGet() == 0U)
    {
        return false;
    }

    tx.id = pdu_can_std_id_encode(PDU_CAN_ID_PMBUS_DBG_DATA);
    tx.rtr = 0U;
    tx.xtd = 0U;
    tx.esi = 0U;
    tx.dlc = 8U;
    tx.brs = 0U;
    tx.fdf = 0U;
    tx.efc = 0U;
    tx.mm = 0U;

    tx.data[0] = trace->seq;
    tx.data[1] = trace->tx[0];
    tx.data[2] = trace->tx[1];
    tx.data[3] = trace->tx[2];
    tx.data[4] = trace->rx[0];
    tx.data[5] = trace->rx[1];
    tx.data[6] = trace->rx[2];
    tx.data[7] = (uint8_t)(((trace->tx_len & 0x0FU) << 4) | (trace->rx_len & 0x0FU));

    return CAN1_MessageTransmitFifo(1U, &tx);
}

static bool pdu_can_send_pmbus_dbg_ext_frame(const pmbus_trace_t *trace)
{
    CAN_TX_BUFFER tx = { 0 };
    uint32_t wait_count = 0UL;

    if (trace == NULL)
    {
        return false;
    }

    (void)pdu_can_recover_if_needed();

    while ((CAN1_TxFifoFreeLevelGet() == 0U) && (wait_count < PDU_CAN_TX_WAIT_LOOPS))
    {
        wait_count++;
    }

    if (CAN1_TxFifoFreeLevelGet() == 0U)
    {
        return false;
    }

    tx.id = pdu_can_std_id_encode(PDU_CAN_ID_PMBUS_DBG_EXT);
    tx.rtr = 0U;
    tx.xtd = 0U;
    tx.esi = 0U;
    tx.dlc = 8U;
    tx.brs = 0U;
    tx.fdf = 0U;
    tx.efc = 0U;
    tx.mm = 0U;

    tx.data[0] = trace->seq;
    tx.data[1] = trace->tx[3];
    tx.data[2] = trace->pec_calc;
    tx.data[3] = trace->pec_rx;
    tx.data[4] = trace->trace_flags;
    tx.data[5] = PDU_PMBUS_PEC_MODE_REQUIRED;
    tx.data[6] = pmbus_get_last_sercom_error();
    tx.data[7] = 0U;

    return CAN1_MessageTransmitFifo(1U, &tx);
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

static void pdu_error_set(uint8_t error_bits)
{
    uint8_t bit;
    for (bit = 0U; bit < 8U; bit++)
    {
        uint8_t mask = (uint8_t)(1U << bit);
        if ((error_bits & mask) != 0U)
        {
            pdu_error_ttl[bit] = PDU_ERROR_TTL_POLLS;
        }
    }
}

static void pdu_error_age(void)
{
    uint8_t bit;
    for (bit = 0U; bit < 8U; bit++)
    {
        if (pdu_error_ttl[bit] > 0U)
        {
            pdu_error_ttl[bit]--;
        }
    }
}

static uint8_t pdu_error_bitmap_get(void)
{
    uint8_t bit;
    uint8_t bitmap = 0U;
    for (bit = 0U; bit < 8U; bit++)
    {
        if (pdu_error_ttl[bit] > 0U)
        {
            bitmap |= (uint8_t)(1U << bit);
        }
    }
    return bitmap;
}

static void pdu_error_details_clear(void)
{
    uint8_t i;
    for (i = 0U; i < PDU_ERROR_DETAIL_MAX; i++)
    {
        pdu_error_details[i].active = false;
        pdu_error_details[i].err = 0U;
        pdu_error_details[i].channel = 0xFFU;
        pdu_error_details[i].command = 0U;
        pdu_error_details[i].ttl = 0U;
    }
}

static void pdu_error_details_age(void)
{
    uint8_t i;
    for (i = 0U; i < PDU_ERROR_DETAIL_MAX; i++)
    {
        if (pdu_error_details[i].active)
        {
            if (pdu_error_details[i].ttl > 0U)
            {
                pdu_error_details[i].ttl--;
            }
            if (pdu_error_details[i].ttl == 0U)
            {
                pdu_error_details[i].active = false;
            }
        }
    }
}

static void pdu_error_details_upsert(uint8_t err, uint8_t channel, uint8_t command)
{
    uint8_t i;
    uint8_t free_index = 0xFFU;
    uint8_t replace_index = 0U;
    uint8_t min_ttl = 0xFFU;

    for (i = 0U; i < PDU_ERROR_DETAIL_MAX; i++)
    {
        if (pdu_error_details[i].active)
        {
            if ((pdu_error_details[i].err == err) &&
                (pdu_error_details[i].channel == channel) &&
                (pdu_error_details[i].command == command))
            {
                pdu_error_details[i].ttl = PDU_ERROR_TTL_POLLS;
                return;
            }

            if (pdu_error_details[i].ttl < min_ttl)
            {
                min_ttl = pdu_error_details[i].ttl;
                replace_index = i;
            }
        }
        else if (free_index == 0xFFU)
        {
            free_index = i;
        }
    }

    i = (free_index != 0xFFU) ? free_index : replace_index;
    pdu_error_details[i].active = true;
    pdu_error_details[i].err = err;
    pdu_error_details[i].channel = channel;
    pdu_error_details[i].command = command;
    pdu_error_details[i].ttl = PDU_ERROR_TTL_POLLS;
}

static bool pdu_can_send_error_detail_frame(uint8_t slot)
{
    CAN_TX_BUFFER tx = { 0 };
    uint32_t wait_count = 0UL;
    pdu_error_detail_t *entry;

    if (slot >= PDU_ERROR_DETAIL_MAX)
    {
        return false;
    }

    (void)pdu_can_recover_if_needed();

    while ((CAN1_TxFifoFreeLevelGet() == 0U) && (wait_count < PDU_CAN_TX_WAIT_LOOPS))
    {
        wait_count++;
    }

    if (CAN1_TxFifoFreeLevelGet() == 0U)
    {
        return false;
    }

    entry = &pdu_error_details[slot];

    tx.id = pdu_can_std_id_encode((uint16_t)(PDU_CAN_ID_ERR_DETAIL_BASE + slot));
    tx.rtr = 0U;
    tx.xtd = 0U;
    tx.esi = 0U;
    tx.dlc = 8U;
    tx.brs = 0U;
    tx.fdf = 0U;
    tx.efc = 0U;
    tx.mm = 0U;

    tx.data[0] = slot;
    tx.data[1] = entry->active ? 1U : 0U;
    tx.data[2] = entry->err;
    tx.data[3] = entry->channel;
    tx.data[4] = entry->command;
    tx.data[5] = entry->ttl;
    tx.data[6] = 0U;
    tx.data[7] = 0U;

    return CAN1_MessageTransmitFifo(1U, &tx);
}

static void pdu_i2c_scan_update(void)
{
    uint8_t found_addrs[128];
    uint8_t n_found = 0U;
    uint8_t i;

    for (i = 0U; i < PDU_I2C_SCAN_FRAME_COUNT; i++)
    {
        pdu_i2c_scan_masks[i] = 0U;
    }

    /*
     * PIC32CM SERCOM I2C errata: status error bits are not always auto-cleared.
     * Force a clean controller state before scanning.
     */
    SERCOM1_I2C_TransferAbort();

    if (!SERCOM1_I2C_BusScan(PDU_I2C_SCAN_START_ADDR, PDU_I2C_SCAN_END_ADDR, found_addrs, &n_found))
    {
        pdu_error_set(PDU_ERR_NACK_OR_BUS);
        pdu_error_details_upsert(PDU_ERR_CODE_ENABLE_FAIL, 0xFFU, 0xFEU);
        pdu_i2c_scan_found = 0U;
        return;
    }

    pdu_i2c_scan_found = n_found;

    if (n_found == 0U)
    {
        pdu_error_set(PDU_ERR_SCAN_NO_ACK);
        pdu_error_details_upsert(PDU_ERR_CODE_SCAN_NO_ACK, 0xFFU, 0xFDU);
    }

    for (i = 0U; i < n_found; i++)
    {
        uint8_t addr = found_addrs[i];
        if ((addr >= PDU_I2C_SCAN_START_ADDR) && (addr <= PDU_I2C_SCAN_END_ADDR))
        {
            uint8_t offset = (uint8_t)(addr - PDU_I2C_SCAN_START_ADDR);
            uint8_t frame = (uint8_t)(offset / 8U);
            uint8_t bit = (uint8_t)(offset % 8U);
            pdu_i2c_scan_masks[frame] |= (uint8_t)(1U << bit);
        }
    }
}

static bool pdu_can_send_i2c_scan_frame(uint8_t slot)
{
    CAN_TX_BUFFER tx = { 0 };
    uint32_t wait_count = 0UL;
    uint8_t base_addr;

    if (slot >= PDU_I2C_SCAN_FRAME_COUNT)
    {
        return false;
    }

    (void)pdu_can_recover_if_needed();

    while ((CAN1_TxFifoFreeLevelGet() == 0U) && (wait_count < PDU_CAN_TX_WAIT_LOOPS))
    {
        wait_count++;
    }

    if (CAN1_TxFifoFreeLevelGet() == 0U)
    {
        return false;
    }

    base_addr = (uint8_t)(PDU_I2C_SCAN_START_ADDR + (slot * 8U));

    tx.id = pdu_can_std_id_encode((uint16_t)(PDU_CAN_ID_I2C_SCAN_BASE + slot));
    tx.rtr = 0U;
    tx.xtd = 0U;
    tx.esi = 0U;
    tx.dlc = 8U;
    tx.brs = 0U;
    tx.fdf = 0U;
    tx.efc = 0U;
    tx.mm = 0U;

    tx.data[0] = slot;
    tx.data[1] = base_addr;
    tx.data[2] = pdu_i2c_scan_masks[slot];
    tx.data[3] = pdu_i2c_scan_found;
    tx.data[4] = PDU_I2C_SCAN_START_ADDR;
    tx.data[5] = PDU_I2C_SCAN_END_ADDR;
    tx.data[6] = 0U;
    tx.data[7] = 0U;

    return CAN1_MessageTransmitFifo(1U, &tx);
}

static void pdu_i2c_scan_report_send_all(void)
{
    uint8_t slot;
    for (slot = 0U; slot < PDU_I2C_SCAN_FRAME_COUNT; slot++)
    {
        (void)pdu_can_send_i2c_scan_frame(slot);
    }
}

static void pdu_i2c_scan_report_if_needed(void)
{
    uint8_t slot;
    bool changed = false;

    for (slot = 0U; slot < PDU_I2C_SCAN_FRAME_COUNT; slot++)
    {
        if (pdu_i2c_scan_masks[slot] != pdu_i2c_scan_masks_last[slot])
        {
            changed = true;
            break;
        }
    }

    if (pdu_i2c_scan_found != pdu_i2c_scan_found_last)
    {
        changed = true;
    }

    pdu_i2c_scan_report_div++;
    if (changed || (pdu_i2c_scan_report_div >= 10U))
    {
        pdu_i2c_scan_report_send_all();
        pdu_i2c_scan_report_div = 0U;

        for (slot = 0U; slot < PDU_I2C_SCAN_FRAME_COUNT; slot++)
        {
            pdu_i2c_scan_masks_last[slot] = pdu_i2c_scan_masks[slot];
        }
        pdu_i2c_scan_found_last = pdu_i2c_scan_found;
    }
}

static void pdu_note_pmbus_error(pmbus_status_t st, uint8_t channel, uint8_t command)
{
    uint8_t err_code;

    err_code = pdu_pmbus_status_to_error_code(st);

    pdu_error_set(PDU_ERR_READ_FAIL);
    pdu_error_details_upsert(err_code, channel, command);
    if (pdu_fail_channel == 0xFFU)
    {
        pdu_last_error = err_code;
        pdu_fail_channel = channel;
        pdu_fail_command = command;
    }

    if (st == PMBUS_PEC_ERROR)
    {
        pdu_error_set(PDU_ERR_PEC_FAIL);
    }
    else if (st == PMBUS_TIMEOUT)
    {
        pdu_error_set(PDU_ERR_TIMEOUT);
    }
    else if ((st == PMBUS_NACK) || (st == PMBUS_BUS_ERROR))
    {
        pdu_error_set(PDU_ERR_NACK_OR_BUS);
    }
}

void PDU_Init(void)
{
    uint8_t bit;
    SERCOM_I2C_TRANSFER_SETUP i2c_setup = { 0 };

    PDU_CAN_Init();

    i2c_setup.clkSpeed = 100000UL;
    (void)SERCOM1_I2C_TransferSetup(&i2c_setup, 0U);

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

    for (bit = 0U; bit < 8U; bit++)
    {
        pdu_error_ttl[bit] = 0U;
    }

    pdu_error_details_clear();
}

void PDU_RunChecks(void)
{
    bool en_ok;

    pdu_debug_stage = PDU_STAGE_RUNCHECKS;

    pdu_enable_all_gpio_outputs();
    en_ok = pdu_enable_all_pmbus_outputs();
    if (!en_ok) {
        pdu_error_set(PDU_ERR_ENABLE_FAIL);
        pdu_error_details_upsert(PDU_ERR_CODE_ENABLE_FAIL, 0xFFU, PMBUS_CMD_OPERATION);
    }
}

void PDU_PollAndSendTelemetry(void)
{
    uint8_t i;
    uint8_t detail_slot;
    uint8_t flt_bitmap = 0U;
    uint16_t shunt_ma = 0U;
    pmbus_trace_t pmbus_trace;
    uint8_t cycle_ok_count = 0U;

    pdu_debug_stage = PDU_STAGE_TELEMETRY;
    pdu_error_age();
    pdu_error_details_age();
    pdu_fail_channel = 0xFFU;
    pdu_fail_command = 0U;
    pdu_last_error = 0U;

    pdu_i2c_scan_div++;
    if (pdu_i2c_scan_div >= 10U)
    {
        pdu_i2c_scan_div = 0U;
        pdu_i2c_scan_update();
        pdu_i2c_scan_report_if_needed();
    }

    for (i = 0U; i < PDU_NUM_EFUSES; i++)
    {
        uint16_t vraw = 0U;
        uint16_t iraw = 0U;
        uint16_t praw = 0U;
        uint16_t mv = 0U;
        uint16_t ma = 0U;
        uint16_t p_10mw = 0U;
        uint16_t adc_ma = 0U;
        uint16_t adc_mv = 0U;
        uint16_t diff_ma = 0U;
        uint16_t status = 0xFFFFU;
        uint8_t adc_flags = PDU_ADC_FLAG_VALID;
        float adc_voltage_v;
        float adc_current_a;
        float pmbus_current_a = 0.0f;
        float adc_diff_a = 0.0f;
        pmbus_status_t st;
        uint8_t failed_cmd = PMBUS_CMD_READ_VOUT;

        adc_voltage_v = PDU_ADC_ReadVoltage(pdu_adc_channels[i]);
        adc_current_a = PDU_ADC_ReadImonCurrent(pdu_adc_channels[i], pdu_r_imon_ohms[i]);
        adc_mv = pdu_float_to_u16_scaled(adc_voltage_v, 1000.0f);
        adc_ma = pdu_float_to_u16_scaled(adc_current_a, 1000.0f);

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
            cycle_ok_count++;
            mv = pdu_float_to_u16_scaled(tps25990_decode_vout(vraw), 1000.0f);
            pmbus_current_a = tps25990_decode_iin_with_r_imon(iraw, pdu_r_imon_ohms[i]);
            ma = pdu_float_to_u16_scaled(pmbus_current_a, 1000.0f);
            p_10mw = pdu_float_to_u16_scaled(tps25990_decode_pin_with_r_imon(praw, pdu_r_imon_ohms[i]), 100.0f);
            adc_flags |= PDU_ADC_FLAG_PMBUS_VALID;

            if (pdu_adc_current_mismatch(pmbus_current_a, adc_current_a, &adc_diff_a))
            {
                adc_flags |= PDU_ADC_FLAG_MISMATCH;
                pdu_error_details_upsert(PDU_ERR_CODE_ADC_MISMATCH, i, PDU_ADC_COMPARE_CMD);
                if (pdu_fail_channel == 0xFFU)
                {
                    pdu_last_error = PDU_ERR_CODE_ADC_MISMATCH;
                    pdu_fail_channel = i;
                    pdu_fail_command = PDU_ADC_COMPARE_CMD;
                }
            }

            diff_ma = pdu_float_to_u16_scaled(adc_diff_a, 1000.0f);

            if ((mv == 0U) && (ma == 0U) && (p_10mw == 0U)) {
                pdu_error_set(PDU_ERR_ZERO_TELEM);
            }
        }
        else
        {
            pdu_note_pmbus_error(st, i, failed_cmd);
        }

        if (!pdu_can_send_efuse_frame((uint16_t)(PDU_CAN_ID_EFUSE_BASE + i), mv, ma, p_10mw, status)) {
            pdu_error_set(PDU_ERR_CAN_TX_FAIL);
            pdu_error_details_upsert(PDU_ERR_CODE_CAN_TX_FAIL, i, 0x00U);
            if (pdu_fail_channel == 0xFFU)
            {
                pdu_last_error = PDU_ERR_CODE_CAN_TX_FAIL;
                pdu_fail_channel = i;
                pdu_fail_command = 0x00U;
            }
        }

        if (!pdu_can_send_adc_frame((uint16_t)(PDU_CAN_ID_ADC_BASE + i), adc_ma, adc_mv, diff_ma, adc_flags)) {
            pdu_error_set(PDU_ERR_CAN_TX_FAIL);
            pdu_error_details_upsert(PDU_ERR_CODE_CAN_TX_FAIL, i, 0x10U);
        }
    }

    if (cycle_ok_count == 0U)
    {
        if (pdu_comm_fail_streak < 250U)
        {
            pdu_comm_fail_streak++;
        }
    }
    else
    {
        pdu_comm_fail_streak = 0U;
    }

    if (pdu_comm_fail_streak >= 5U)
    {
        SERCOM1_I2C_TransferAbort();
        pdu_enable_all_gpio_outputs();
        (void)pdu_enable_all_pmbus_outputs();
        pdu_error_details_upsert(PDU_ERR_CODE_ENABLE_FAIL, 0xFFU, PMBUS_CMD_OPERATION);
        pdu_comm_fail_streak = 0U;
    }

    shunt_ma = pdu_float_to_u16_scaled(PDU_ADC_ReadNonfuseCurrent(), 1000.0f);

    pdu_debug_flags = pdu_error_bitmap_get();

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
        pdu_error_set(PDU_ERR_CAN_TX_FAIL);
        pdu_debug_flags = pdu_error_bitmap_get();
        pdu_error_details_upsert(PDU_ERR_CODE_CAN_TX_FAIL, 0xFFU, 0x00U);
    }

    for (detail_slot = 0U; detail_slot < PDU_ERROR_DETAIL_MAX; detail_slot++)
    {
        (void)pdu_can_send_error_detail_frame(detail_slot);
    }

    while (pmbus_trace_pop(&pmbus_trace))
    {
        bool meta_ok = pdu_can_send_pmbus_dbg_meta_frame(&pmbus_trace);
        bool data_ok = pdu_can_send_pmbus_dbg_data_frame(&pmbus_trace);
        bool ext_ok = pdu_can_send_pmbus_dbg_ext_frame(&pmbus_trace);

        if ((!meta_ok) || (!data_ok) || (!ext_ok))
        {
            pdu_error_set(PDU_ERR_CAN_TX_FAIL);
            pdu_error_details_upsert(PDU_ERR_CODE_CAN_TX_FAIL, 0xFFU, 0x60U);
            break;
        }
    }
}