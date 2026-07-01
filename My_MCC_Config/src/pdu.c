/**
 * @file pdu.c
 * @brief Power Distribution Unit (PDU) â€” Relay-based (Dumb PDU)
 *
 * Controls 8 relay channels via GPIO with CAN-bus command input.
 * Output voltages are sensed by the PIC32CM internal ADC (2.048 V
 * internal reference, oversampled) through 11:1 resistor dividers.
 *
 * No PMBus, no TPS25990, no I2C â€” pure GPIO + ADC + CAN.
 */

#include "pdu.h"
#include "pdu_adc.h"
#include "definitions.h"

/*============================================================================
 * CAN Identifiers
 *===========================================================================*/

#define PDU_CAN_ID_CONTROL_MASK     0x080U   /* RX: ECU output mask        */
#define PDU_CAN_ID_INPUT8_STATUS    0x085U   /* TX: Input8 raw state       */
#define PDU_CAN_ID_CONTROL          0x200U   /* RX: Dashboard override      */
#define PDU_CAN_ID_TELEM_SUMMARY    0x700U   /* TX: Summary frame           */
#define PDU_CAN_ID_TELEM_VOLT_0_3   0x701U   /* TX: Voltages ch 0â€“3         */
#define PDU_CAN_ID_TELEM_VOLT_4_7   0x702U   /* TX: Voltages ch 4â€“7         */
#define PDU_CAN_ID_ECU_RAW_DEBUG    0x703U   /* TX: ECU raw debug (debug)   */
#define PDU_CAN_ID_MCU_TELEM        0x740U   /* TX: MCU debug (debug)       */

/*============================================================================
 * Protocol Constants
 *===========================================================================*/

#define PDU_CONTROL_MAGIC            0xA5U
#define PDU_CONTROL_OP_OUTPUT        0x01U
#define PDU_CONTROL_OP_CLEAR_FAULTS  0x03U
#define PDU_CONTROL_OP_NOP           0x00U
#define PDU_CONTROL_FLAG_DEBUG       (1U << 2)
#define PDU_OVERRIDE_FLAG_ARMED      (1U << 0)
#define PDU_OVERRIDE_FLAG_START_ON   (1U << 1)

#define PDU_CONTROL_SOURCE_TIMEOUT_MS  500U
#define PDU_DEBUG_TTL_POLLS            10U

/* Control-state flag bits (byte 3 of 0x700) */
#define PDU_CTL_DEBUG_ACTIVE       (1U << 0)
#define PDU_CTL_ECU_FRESH          (1U << 1)
#define PDU_CTL_OVERRIDE_FRESH     (1U << 2)
#define PDU_CTL_OVERRIDE_ARMED     (1U << 3)
#define PDU_CTL_OVERRIDE_ACTIVE    (1U << 4)
#define PDU_CTL_SAFETY_BLOCKED     (1U << 5)
#define PDU_CTL_START_ON           (1U << 7)

/* System error flags (byte 2 of 0x700) */
#define PDU_ERR_CAN_TX_FAIL        (1U << 6)

/* ECU raw debug flags */
#define PDU_ECU_RAW_FLAG_SEEN      (1U << 0)
#define PDU_ECU_RAW_FLAG_FRESH     (1U << 1)
#define PDU_ECU_RAW_FLAG_BYTE1     (1U << 2)
#define PDU_ECU_RAW_FLAG_DLC_OK    (1U << 3)

/* Fault bitmap bits (byte 7 of 0x700) */
#define PDU_FLT_BITMAP_FLT         (1U << 0)
#define PDU_FLT_BITMAP_FLTM        (1U << 1)
#define PDU_FLT_BITMAP_SDC         (1U << 2)
#define PDU_FLT_BITMAP_BSPD        (1U << 3)
#define PDU_FLT_BITMAP_BOTS        (1U << 4)
#define PDU_FLT_BITMAP_INERTIA     (1U << 5)

/* Safety input bits */
#define PDU_SAFETY_INPUT_SDC       (1U << 0)
#define PDU_SAFETY_INPUT_BSPD      (1U << 1)
#define PDU_SAFETY_INPUT_BOTS      (1U << 2)
#define PDU_SAFETY_INPUT_INERTIA   (1U << 3)

/* Safety re-enable delay after all inputs clear */
#define PDU_SAFETY_REENABLE_DELAY_MS  500U

/* CAN standard-ID encode/decode */
#define PDU_CAN_STD_ID_SHIFT        18U

/* Input8 CAN values */
#define PDU_INPUT8_ASSERTED         0xFFU
#define PDU_INPUT8_DEASSERTED       0x00U

/* MCU debug stage codes */
#define PDU_STAGE_INIT              1U
#define PDU_STAGE_RUNCHECKS         2U
#define PDU_STAGE_TELEMETRY         3U

/*============================================================================
 * GPIO Output Pin Map
 *===========================================================================*/

static void pdu_gpio_set(uint8_t ch, bool on)
{
    switch (ch)
    {
        case 0U: if (on) GPIO_HYBRID_Set();  else GPIO_HYBRID_Clear();  break;
        case 1U: if (on) GPIO_VENT1_Set();   else GPIO_VENT1_Clear();   break;
        case 2U: if (on) GPIO_VENT2_Set();   else GPIO_VENT2_Clear();   break;
        case 3U: if (on) GPIO_IGNINJ_Set();  else GPIO_IGNINJ_Clear();  break;
        case 4U: if (on) GPIO_FUEL_P_Set();  else GPIO_FUEL_P_Clear();  break;
        case 5U: if (on) GPIO_WP1_Set();     else GPIO_WP1_Clear();     break;
        case 6U: if (on) GPIO_WP2_Set();     else GPIO_WP2_Clear();     break;
        case 7U: if (on) GPIO_EN12V_E_Set(); else GPIO_EN12V_E_Clear(); break;
        default: break;
    }
}

static void pdu_gpio_start_set(bool on)
{
    if (on) { GPIO_START_Set(); } else { GPIO_START_Clear(); }
}

static void pdu_gpio_enable_all(void)
{
    GPIO_HYBRID_OutputEnable();
    GPIO_VENT1_OutputEnable();
    GPIO_VENT2_OutputEnable();
    GPIO_IGNINJ_OutputEnable();
    GPIO_FUEL_P_OutputEnable();
    GPIO_WP1_OutputEnable();
    GPIO_WP2_OutputEnable();
    GPIO_EN12V_E_OutputEnable();
    GPIO_START_OutputEnable();

    /* Start with all high (relay drivers active-low? No â€” active-high
     * for the MOSFET gate drivers on this board) */
    GPIO_HYBRID_Set();
    GPIO_VENT1_Set();
    GPIO_VENT2_Set();
    GPIO_IGNINJ_Set();
    GPIO_FUEL_P_Set();
    GPIO_WP1_Set();
    GPIO_WP2_Set();
    GPIO_EN12V_E_Set();
    GPIO_START_Set();
}

/*============================================================================
 * ADC Channel Mapping
 *===========================================================================*/

static const pdu_adc_channel_t pdu_adc_map[PDU_NUM_CHANNELS] =
{
    PDU_ADC_VSENSE_HYBRID,
    PDU_ADC_VSENSE_VENT1,
    PDU_ADC_VSENSE_VENT2,
    PDU_ADC_VSENSE_IGN,
    PDU_ADC_VSENSE_FUEL,
    PDU_ADC_VSENSE_WP1,
    PDU_ADC_VSENSE_WP2,
    PDU_ADC_VSENSE_12V
};

/*============================================================================
 * Global State
 *===========================================================================*/

static uint8_t can0_msg_ram[CAN0_MESSAGE_RAM_CONFIG_SIZE] __attribute__((aligned(4)));

/* â”€â”€ Output control â”€â”€ */
static volatile uint8_t  pdu_ecu_output_mask;         /* from 0x080 CAN RX */
static volatile uint32_t pdu_ecu_output_mask_ms;
static volatile bool     pdu_ecu_output_mask_valid;

static volatile uint8_t  pdu_dashboard_override_mask;  /* from 0x200 CAN RX */
static volatile uint32_t pdu_dashboard_override_ms;
static volatile bool     pdu_dashboard_override_valid;
static volatile bool     pdu_dashboard_override_armed;
static volatile bool     pdu_dashboard_override_start = true;

static uint8_t  pdu_requested_mask;
static uint8_t  pdu_applied_mask;
static uint8_t  pdu_active_control_source;   /* 0=none, 1=ECU, 2=dashboard */
static bool     pdu_desired_start_enabled = true;

/* â”€â”€ Safety â”€â”€ */
static volatile uint8_t  pdu_safety_input_bits;
static volatile bool     pdu_safety_input_changed;
static volatile bool     pdu_safety_refresh_pending;
static bool              pdu_safety_inhibit_active;
static bool              pdu_safety_release_pending;
static uint32_t          pdu_safety_release_start_ms;

/* â”€â”€ ECU raw debug â”€â”€ */
static volatile uint8_t  pdu_ecu_raw_byte0;
static volatile uint8_t  pdu_ecu_raw_byte1;
static volatile uint8_t  pdu_ecu_raw_dlc;
static volatile bool     pdu_ecu_raw_seen;
static volatile bool     pdu_ecu_raw_used_byte1;
static volatile uint8_t  pdu_ecu_raw_requested_mask;
static volatile uint16_t pdu_ecu_raw_rx_count;

/* â”€â”€ Debug / telemetry â”€â”€ */
static volatile uint8_t  pdu_debug_ttl_polls;
static volatile uint32_t pdu_uptime_ms;
static volatile bool     pdu_control_service_pending;
static volatile bool     pdu_telemetry_service_pending;
static uint8_t           pdu_debug_stage = PDU_STAGE_INIT;
static uint8_t           pdu_system_flags;
static float             pdu_voltages[PDU_NUM_CHANNELS];   /* latest mV readings */

/* Desired state (resolved from control sources) */
static bool pdu_desired_channel_on[PDU_NUM_CHANNELS];

/*============================================================================
 * Forward Declarations
 *===========================================================================*/

static void pdu_can_rx_fifo_callback(uint8_t numberOfMessage, uintptr_t contextHandle);
static void pdu_tc0_timer_callback(TC_TIMER_STATUS status, uintptr_t context);
static void pdu_safety_input_callback(uintptr_t context);
static void pdu_resolve_output_control(void);
static void pdu_apply_outputs(void);
static void pdu_process_control_can(void);
static bool pdu_can_tx_fifo_ready(void);
static bool pdu_can_recover_if_needed(void);

/*============================================================================
 * CAN Helpers
 *===========================================================================*/

static uint32_t pdu_can_std_id_encode(uint16_t std_id)
{
    return ((uint32_t)(std_id & 0x7FFU)) << PDU_CAN_STD_ID_SHIFT;
}

static bool pdu_can_recover_if_needed(void)
{
    CAN_ERROR err = CAN0_ErrorGet();
    if ((err & CAN_ERROR_BUS_OFF) != 0U)
    {
        /* Attempt auto-recovery from bus-off */
        uint8_t tx_err, rx_err;
        CAN0_ErrorCountGet(&tx_err, &rx_err);
        (void)tx_err;
        (void)rx_err;
    }
    return true;
}

static bool pdu_can_tx_fifo_ready(void)
{
    /* CAN0_TxFifoFreeLevelGet returns number of free TX-FIFO slots */
    return (CAN0_TxFifoFreeLevelGet() > 0U);
}

static bool pdu_can_send_8byte(uint16_t std_id, const uint8_t data[8])
{
    CAN_TX_BUFFER tx = { 0 };

    (void)pdu_can_recover_if_needed();
    if (!pdu_can_tx_fifo_ready())
    {
        pdu_system_flags |= PDU_ERR_CAN_TX_FAIL;
        return false;
    }

    tx.id  = pdu_can_std_id_encode(std_id);
    tx.dlc = 8U;
    tx.data[0] = data[0];  tx.data[1] = data[1];
    tx.data[2] = data[2];  tx.data[3] = data[3];
    tx.data[4] = data[4];  tx.data[5] = data[5];
    tx.data[6] = data[6];  tx.data[7] = data[7];

    return CAN0_MessageTransmitFifo(1U, &tx);
}

/*============================================================================
 * Safety-Interlock Helpers
 *===========================================================================*/

static bool pdu_is_safety_channel(uint8_t ch)
{
    return (ch == 0U) || (ch == 3U) || (ch == 4U);  /* Hybrid, IGN, Fuel */
}

static bool pdu_safety_blocked(void)
{
    return pdu_safety_inhibit_active || pdu_safety_release_pending;
}

static uint8_t pdu_read_safety_inputs(void)
{
    uint8_t bits = 0U;
    if (SDC_Get()     != 0U) { bits |= PDU_SAFETY_INPUT_SDC;      }
    if (BSPD_Get()    != 0U) { bits |= PDU_SAFETY_INPUT_BSPD;     }
    if (BOTS_Get()    != 0U) { bits |= PDU_SAFETY_INPUT_BOTS;     }
    if (INERTIA_Get() != 0U) { bits |= PDU_SAFETY_INPUT_INERTIA;  }
    return bits;
}

static void pdu_force_safety_off(void)
{
    pdu_gpio_set(0U, false);  /* Hybrid  */
    pdu_gpio_set(3U, false);  /* IGN/INJ */
    pdu_gpio_set(4U, false);  /* Fuel    */
}

static void pdu_service_safety_inputs(void)
{
    uint8_t active = pdu_safety_input_bits;

    /* â”€â”€ Rising edge: safety triggered â”€â”€ */
    if (pdu_safety_input_changed)
    {
        pdu_safety_input_changed = false;
        if (active != 0U)
        {
            pdu_force_safety_off();
            pdu_safety_inhibit_active  = true;
            pdu_safety_release_pending = false;
        }
        else if (pdu_safety_inhibit_active)
        {
            /* All inputs cleared â€” start release timer */
            pdu_safety_inhibit_active   = false;
            pdu_safety_release_pending  = true;
            pdu_safety_release_start_ms = pdu_uptime_ms;
        }
    }

    /* â”€â”€ Release timer expired? â”€â”€ */
    if (pdu_safety_release_pending)
    {
        if (active != 0U)
        {
            /* Re-triggered while waiting */
            pdu_safety_release_pending = false;
            pdu_safety_inhibit_active  = true;
        }
        else if ((pdu_uptime_ms - pdu_safety_release_start_ms)
                  >= PDU_SAFETY_REENABLE_DELAY_MS)
        {
            pdu_safety_release_pending = false;
            /* Re-apply desired state on safety channels */
            pdu_safety_refresh_pending = true;
        }
    }
}

/*============================================================================
 * Output Control
 *===========================================================================*/

static bool pdu_control_is_fresh(uint32_t timestamp_ms, uint32_t timeout_ms)
{
    return ((uint32_t)(pdu_uptime_ms - timestamp_ms) <= timeout_ms);
}

static bool pdu_ecu_is_fresh(void)
{
    return pdu_ecu_output_mask_valid &&
           pdu_control_is_fresh(pdu_ecu_output_mask_ms,
                                PDU_CONTROL_SOURCE_TIMEOUT_MS);
}

static bool pdu_override_is_fresh(void)
{
    return pdu_dashboard_override_valid &&
           pdu_control_is_fresh(pdu_dashboard_override_ms,
                                PDU_CONTROL_SOURCE_TIMEOUT_MS);
}

static void pdu_resolve_output_control(void)
{
    uint8_t mask;
    uint8_t source = 0U;
    bool    start  = true;

    if (pdu_dashboard_override_armed && pdu_override_is_fresh())
    {
        source = 2U;
        mask   = pdu_dashboard_override_mask;
        start  = pdu_dashboard_override_start;
    }
    else if (pdu_ecu_is_fresh())
    {
        source = 1U;
        mask   = pdu_ecu_output_mask;
        start  = true;
    }
    else
    {
        mask = 0x00U;
    }

    pdu_active_control_source  = source;
    pdu_requested_mask         = mask;
    pdu_desired_start_enabled  = start;

    for (uint8_t ch = 0U; ch < PDU_NUM_CHANNELS; ch++)
    {
        pdu_desired_channel_on[ch] = ((mask >> ch) & 1U) != 0U;
    }
}

static void pdu_apply_outputs(void)
{
    uint8_t ch;
    bool    blocked = pdu_safety_blocked();

    pdu_resolve_output_control();

    for (ch = 0U; ch < PDU_NUM_CHANNELS; ch++)
    {
        bool on = pdu_desired_channel_on[ch];

        if (blocked && pdu_is_safety_channel(ch))
        {
            on = false;
        }

        pdu_gpio_set(ch, on);
    }

    pdu_gpio_start_set(pdu_desired_start_enabled);
    pdu_applied_mask = pdu_requested_mask;

    /* Safety channels are forced off when blocked */
    if (blocked)
    {
        pdu_applied_mask &= (uint8_t)(~((1U << 0U) | (1U << 3U) | (1U << 4U)));
    }
}

/*============================================================================
 * CAN RX Processing
 *===========================================================================*/

static uint8_t pdu_decode_ecu_mask(const CAN_RX_BUFFER *rx)
{
    if ((rx == NULL) || (rx->dlc == 0U))
    {
        return 0U;
    }

    /* Byte1 protocol: if byte0 == 0 and byte1 != 0, use byte1 */
    if ((rx->dlc >= 2U) && (rx->data[0] == 0U) && (rx->data[1] != 0U))
    {
        return rx->data[1];
    }

    return rx->data[0];
}

static void pdu_process_control_can(void)
{
    CAN_RX_BUFFER rx = { 0 };

    while ((CAN0_REGS->CAN_RXF0S & CAN_RXF0S_F0FL_Msk) != 0U)
    {
        if (!CAN0_MessageReceiveFifo(CAN_RX_FIFO_0, 1U, &rx))
        {
            continue;
        }

        uint16_t can_id = (uint16_t)((rx.id >> PDU_CAN_STD_ID_SHIFT) & 0x7FFU);

        /* â”€â”€ 0x080: ECU output mask â€” instant GPIO set â”€â”€ */
        if (can_id == PDU_CAN_ID_CONTROL_MASK)
        {
            uint8_t mask = pdu_decode_ecu_mask(&rx);

            /* Raw debug capture */
            pdu_ecu_raw_seen        = true;
            pdu_ecu_raw_dlc         = rx.dlc;
            pdu_ecu_raw_byte0       = (rx.dlc >= 1U) ? rx.data[0] : 0U;
            pdu_ecu_raw_byte1       = (rx.dlc >= 2U) ? rx.data[1] : 0U;
            pdu_ecu_raw_used_byte1  = ((rx.dlc >= 2U) && (rx.data[0] == 0U) && (rx.data[1] != 0U));
            pdu_ecu_raw_requested_mask = mask;
            pdu_ecu_raw_rx_count++;

            pdu_ecu_output_mask     = mask;
            pdu_ecu_output_mask_ms  = pdu_uptime_ms;
            pdu_ecu_output_mask_valid = true;

            /* Instant apply â€” set GPIOs immediately from interrupt context
             * (safe because GPIO_Set/Clear are atomic bit-band writes) */
            bool blocked = pdu_safety_blocked();
            for (uint8_t ch = 0U; ch < PDU_NUM_CHANNELS; ch++)
            {
                bool on = ((mask >> ch) & 1U) != 0U;
                if (blocked && pdu_is_safety_channel(ch))
                {
                    on = false;
                }
                pdu_gpio_set(ch, on);
            }
            pdu_gpio_start_set(true);
            pdu_applied_mask = blocked
                ? (mask & (uint8_t)(~((1U << 0U) | (1U << 3U) | (1U << 4U))))
                : mask;
            pdu_dashboard_override_armed = false;  /* ECU preempts dashboard */
        }

        /* â”€â”€ 0x200: Dashboard override control â”€â”€ */
        else if (can_id == PDU_CAN_ID_CONTROL)
        {
            if (rx.dlc >= 5U && rx.data[4] == PDU_CONTROL_MAGIC)
            {
                uint8_t opcode = rx.data[0];
                uint8_t param0 = rx.data[1];
                uint8_t flags  = rx.data[3];

                if (opcode == PDU_CONTROL_OP_OUTPUT)
                {
                    pdu_dashboard_override_mask   = param0;
                    pdu_dashboard_override_armed  = (flags & PDU_OVERRIDE_FLAG_ARMED) != 0U;
                    pdu_dashboard_override_start  = (flags & PDU_OVERRIDE_FLAG_START_ON) != 0U;
                    pdu_dashboard_override_ms     = pdu_uptime_ms;
                    pdu_dashboard_override_valid  = true;
                }
                else if (opcode == PDU_CONTROL_OP_CLEAR_FAULTS)
                {
                    /* No-op on dumb PDU â€” just acknowledge */
                }
                /* Debug TTL pulse */
                if ((flags & PDU_CONTROL_FLAG_DEBUG) != 0U)
                {
                    pdu_debug_ttl_polls = PDU_DEBUG_TTL_POLLS;
                }
            }
        }
    }
}

/*============================================================================
 * Interrupt Callbacks
 *===========================================================================*/

static void pdu_can_rx_fifo_callback(uint8_t numberOfMessage, uintptr_t contextHandle)
{
    (void)numberOfMessage;
    (void)contextHandle;
    pdu_process_control_can();
}

static void pdu_tc0_timer_callback(TC_TIMER_STATUS status, uintptr_t context)
{
    static uint8_t control_div   = 0U;
    static uint8_t telemetry_div = 0U;

    (void)context;

    if ((status & TC_TIMER_STATUS_OVERFLOW) == 0U)
    {
        return;
    }

    pdu_uptime_ms++;

    /* 100 Hz control service */
    control_div++;
    if (control_div >= 10U)
    {
        control_div = 0U;
        pdu_control_service_pending = true;
    }

    /* 20 Hz telemetry */
    telemetry_div++;
    if (telemetry_div >= 50U)
    {
        telemetry_div = 0U;
        pdu_telemetry_service_pending = true;
    }
}

static void pdu_safety_input_callback(uintptr_t context)
{
    (void)context;

    uint8_t sampled = pdu_read_safety_inputs();
    if (sampled == pdu_safety_input_bits)
    {
        return;
    }

    pdu_safety_input_bits    = sampled;
    pdu_safety_input_changed = true;

    if (sampled != 0U)
    {
        pdu_force_safety_off();
        pdu_safety_refresh_pending  = true;
    }

    pdu_control_service_pending = true;
}

/*============================================================================
 * Telemetry Transmission
 *===========================================================================*/

static uint8_t pdu_get_control_state_flags(void)
{
    uint8_t flags = 0U;

    if (pdu_debug_ttl_polls > 0U)                        { flags |= PDU_CTL_DEBUG_ACTIVE;    }
    if (pdu_ecu_is_fresh())                               { flags |= PDU_CTL_ECU_FRESH;       }
    if (pdu_override_is_fresh())                          { flags |= PDU_CTL_OVERRIDE_FRESH;  }
    if (pdu_dashboard_override_armed)                     { flags |= PDU_CTL_OVERRIDE_ARMED;  }
    if (pdu_active_control_source == 2U)                   { flags |= PDU_CTL_OVERRIDE_ACTIVE; }
    if (pdu_safety_blocked())                             { flags |= PDU_CTL_SAFETY_BLOCKED;  }
    if (pdu_desired_start_enabled)                        { flags |= PDU_CTL_START_ON;        }

    return flags;
}

static uint8_t pdu_get_ecu_raw_debug_flags(void)
{
    uint8_t flags = 0U;
    if (pdu_ecu_raw_seen)        { flags |= PDU_ECU_RAW_FLAG_SEEN;   }
    if (pdu_ecu_is_fresh())      { flags |= PDU_ECU_RAW_FLAG_FRESH;  }
    if (pdu_ecu_raw_used_byte1)  { flags |= PDU_ECU_RAW_FLAG_BYTE1;  }
    if (pdu_ecu_raw_dlc >= 1U)   { flags |= PDU_ECU_RAW_FLAG_DLC_OK; }
    return flags;
}

static uint8_t pdu_get_input8_status(void)
{
    return (GPIO_PB15_Get() == 0U) ? PDU_INPUT8_ASSERTED : PDU_INPUT8_DEASSERTED;
}

static uint8_t pdu_get_fault_bitmap(void)
{
    uint8_t bits = 0U;
    if (FLT_Get()  == 0U) { bits |= PDU_FLT_BITMAP_FLT;      }
    if (FLTM_Get() == 0U) { bits |= PDU_FLT_BITMAP_FLTM;     }
    if ((pdu_safety_input_bits & PDU_SAFETY_INPUT_SDC)     != 0U) { bits |= PDU_FLT_BITMAP_SDC;     }
    if ((pdu_safety_input_bits & PDU_SAFETY_INPUT_BSPD)    != 0U) { bits |= PDU_FLT_BITMAP_BSPD;    }
    if ((pdu_safety_input_bits & PDU_SAFETY_INPUT_BOTS)    != 0U) { bits |= PDU_FLT_BITMAP_BOTS;    }
    if ((pdu_safety_input_bits & PDU_SAFETY_INPUT_INERTIA) != 0U) { bits |= PDU_FLT_BITMAP_INERTIA; }
    return bits;
}

static void pdu_send_telemetry(void)
{
    uint8_t  data[8];
    uint8_t  ch;
    uint16_t vin_mv;
    uint8_t  ecu_mask = pdu_ecu_is_fresh() ? pdu_ecu_output_mask : 0U;
    uint8_t  dash_mask = (pdu_dashboard_override_armed && pdu_override_is_fresh())
                            ? pdu_dashboard_override_mask : 0U;

    pdu_debug_stage = PDU_STAGE_TELEMETRY;

    /* â”€â”€ Read all 8 ADC channels â”€â”€ */
    for (ch = 0U; ch < PDU_NUM_CHANNELS; ch++)
    {
        pdu_voltages[ch] = PDU_ADC_ReadChannelVoltage(pdu_adc_map[ch]);
    }

    /* VIN = channel 7 (12V bus) voltage in mV */
    vin_mv = (uint16_t)(pdu_voltages[7U] * 1000.0f);

    /* â”€â”€ 0x700: Summary â”€â”€ */
    data[0] = (uint8_t)(vin_mv & 0xFFU);
    data[1] = (uint8_t)((vin_mv >> 8) & 0xFFU);
    data[2] = pdu_system_flags;
    data[3] = pdu_get_control_state_flags();
    data[4] = pdu_requested_mask;
    data[5] = pdu_applied_mask;
    data[6] = ecu_mask;
    data[7] = dash_mask;
    (void)pdu_can_send_8byte(PDU_CAN_ID_TELEM_SUMMARY, data);

    /* â”€â”€ 0x701: Voltages ch 0â€“3 â”€â”€ */
    for (ch = 0U; ch < 4U; ch++)
    {
        uint16_t mv = (uint16_t)(pdu_voltages[ch] * 1000.0f);
        data[ch * 2U]     = (uint8_t)(mv & 0xFFU);
        data[ch * 2U + 1U] = (uint8_t)((mv >> 8) & 0xFFU);
    }
    (void)pdu_can_send_8byte(PDU_CAN_ID_TELEM_VOLT_0_3, data);

    /* â”€â”€ 0x702: Voltages ch 4â€“7 â”€â”€ */
    for (ch = 0U; ch < 4U; ch++)
    {
        uint16_t mv = (uint16_t)(pdu_voltages[ch + 4U] * 1000.0f);
        data[ch * 2U]     = (uint8_t)(mv & 0xFFU);
        data[ch * 2U + 1U] = (uint8_t)((mv >> 8) & 0xFFU);
    }
    (void)pdu_can_send_8byte(PDU_CAN_ID_TELEM_VOLT_4_7, data);

    /* â”€â”€ 0x085: Input8 status â”€â”€ */
    {
        CAN_TX_BUFFER tx = { 0 };
        (void)pdu_can_recover_if_needed();
        if (pdu_can_tx_fifo_ready())
        {
            tx.id    = pdu_can_std_id_encode(PDU_CAN_ID_INPUT8_STATUS);
            tx.dlc   = 1U;
            tx.data[0] = pdu_get_input8_status();
            (void)CAN0_MessageTransmitFifo(1U, &tx);
        }
    }

    /* â”€â”€ Debug-mode-only frames â”€â”€ */
    if (pdu_debug_ttl_polls > 0U)
    {
        /* MCU debug: 0x740 */
        {
            uint8_t flt_bm = pdu_get_fault_bitmap();
            data[0] = flt_bm;
            data[1] = pdu_system_flags;
            data[2] = 0U;  /* shunt mA lo (no shunt on dumb PDU) */
            data[3] = 0U;  /* shunt mA hi */
            data[4] = pdu_debug_stage;
            data[5] = 0U;  /* last error code */
            data[6] = 0xFFU; /* fail channel */
            data[7] = 0U;  /* fail command */
            (void)pdu_can_send_8byte(PDU_CAN_ID_MCU_TELEM, data);
        }

        /* ECU raw debug: 0x703 */
        {
            uint8_t ecu_flags  = pdu_get_ecu_raw_debug_flags();
            uint8_t ecu_decoded = pdu_ecu_is_fresh() ? pdu_ecu_output_mask : 0U;
            data[0] = ecu_flags;
            data[1] = ecu_decoded;
            data[2] = pdu_ecu_raw_byte0;
            data[3] = pdu_ecu_raw_byte1;
            data[4] = pdu_ecu_raw_dlc;
            data[5] = (uint8_t)(pdu_ecu_raw_rx_count & 0xFFU);
            data[6] = (uint8_t)((pdu_ecu_raw_rx_count >> 8) & 0xFFU);
            data[7] = pdu_ecu_raw_requested_mask;
            (void)pdu_can_send_8byte(PDU_CAN_ID_ECU_RAW_DEBUG, data);
        }

        /* Age debug TTL */
        pdu_debug_ttl_polls--;
    }
}

/*============================================================================
 * Control Service (100 Hz)
 *===========================================================================*/

static void pdu_service_control(void)
{
    pdu_debug_stage = PDU_STAGE_RUNCHECKS;

    /* Poll safety inputs */
    uint8_t sampled = pdu_read_safety_inputs();
    if (sampled != pdu_safety_input_bits)
    {
        pdu_safety_input_bits    = sampled;
        pdu_safety_input_changed = true;
        if (sampled != 0U)
        {
            pdu_force_safety_off();
            pdu_safety_refresh_pending = true;
        }
    }

    pdu_service_safety_inputs();

    /* Refresh safety channels after release */
    if (pdu_safety_refresh_pending && !pdu_safety_blocked())
    {
        pdu_safety_refresh_pending = false;
        pdu_resolve_output_control();
        for (uint8_t ch = 0U; ch < PDU_NUM_CHANNELS; ch++)
        {
            if (pdu_is_safety_channel(ch))
            {
                pdu_gpio_set(ch, pdu_desired_channel_on[ch]);
            }
        }
    }
}

/*============================================================================
 * Public API
 *===========================================================================*/

void PDU_CAN_Init(void)
{
    CAN0_MessageRAMConfigSet(can0_msg_ram);
}

void PDU_Init(void)
{
    PDU_CAN_Init();

    /* â”€â”€ ADC with internal 2.048 V reference â”€â”€ */
    PDU_ADC_Init();

    /* â”€â”€ Enable all GPIO output drivers â”€â”€ */
    pdu_gpio_enable_all();

    /* â”€â”€ CAN RX interrupt on FIFO 0 â”€â”€ */
    CAN0_RxFifoCallbackRegister(CAN_RX_FIFO_0, pdu_can_rx_fifo_callback, 0U);

    /* â”€â”€ TC0 1 ms timer â”€â”€ */
    TC0_TimerCallbackRegister(pdu_tc0_timer_callback, 0U);
    TC0_TimerStart();

    /* â”€â”€ EIC callbacks for safety inputs â”€â”€ */
    EIC_CallbackRegister(EIC_PIN_0, pdu_safety_input_callback, 0U);
    EIC_CallbackRegister(EIC_PIN_1, pdu_safety_input_callback, 0U);
    EIC_CallbackRegister(EIC_PIN_2, pdu_safety_input_callback, 0U);
    EIC_CallbackRegister(EIC_PIN_3, pdu_safety_input_callback, 0U);

    /* â”€â”€ Initialise safety state â”€â”€ */
    pdu_safety_input_bits       = pdu_read_safety_inputs();
    pdu_safety_input_changed    = false;
    pdu_safety_refresh_pending  = false;
    pdu_safety_inhibit_active   = false;
    pdu_safety_release_pending  = false;
    pdu_safety_release_start_ms = 0U;
    pdu_uptime_ms               = 0U;

    pdu_ecu_output_mask      = 0U;
    pdu_ecu_output_mask_ms   = 0U;
    pdu_ecu_output_mask_valid = false;

    pdu_dashboard_override_mask  = 0U;
    pdu_dashboard_override_ms    = 0U;
    pdu_dashboard_override_valid = false;
    pdu_dashboard_override_armed = false;
    pdu_dashboard_override_start = true;

    pdu_requested_mask        = 0U;
    pdu_applied_mask          = 0U;
    pdu_active_control_source = 0U;
    pdu_desired_start_enabled = true;
    pdu_debug_ttl_polls       = 0U;
    pdu_system_flags          = 0U;
    pdu_debug_stage           = PDU_STAGE_INIT;

    pdu_ecu_raw_seen          = false;
    pdu_ecu_raw_rx_count      = 0U;
    pdu_ecu_raw_byte0         = 0U;
    pdu_ecu_raw_byte1         = 0U;
    pdu_ecu_raw_dlc           = 0U;

    pdu_control_service_pending  = false;
    pdu_telemetry_service_pending = false;

    for (uint8_t ch = 0U; ch < PDU_NUM_CHANNELS; ch++)
    {
        pdu_desired_channel_on[ch] = false;
        pdu_voltages[ch]           = 0.0f;
    }

    /* â”€â”€ Force safety-off if any interlock active at boot â”€â”€ */
    if (pdu_safety_input_bits != 0U)
    {
        pdu_force_safety_off();
        pdu_safety_inhibit_active = true;
    }

    /* â”€â”€ LEDs: active-low, start all off â”€â”€ */
    GPIO_GLED_OutputEnable();
    GPIO_BLED_OutputEnable();
    GPIO_RLED_OutputEnable();
    GPIO_GLED_Set();
    GPIO_BLED_Set();
    GPIO_RLED_Set();

    /* â”€â”€ Apply initial (all-off) outputs â”€â”€ */
    pdu_apply_outputs();
}

void PDU_Service(void)
{
    bool run_control   = pdu_control_service_pending;
    bool run_telemetry = pdu_telemetry_service_pending;

    pdu_control_service_pending   = false;
    pdu_telemetry_service_pending = false;

    if (run_control)
    {
        pdu_service_control();
    }

    if (run_telemetry)
    {
        /* Resolve dashboard-vs-ECU and apply before telemetry */
        pdu_apply_outputs();
        pdu_send_telemetry();
    }
}

void PDU_PollAndSendTelemetry(void)
{
    /* Legacy entry point â€” telemetry is now timer-driven via PDU_Service().
     * Called from main loop for compatibility; no-op if already handled. */
    if (pdu_telemetry_service_pending)
    {
        pdu_telemetry_service_pending = false;
        pdu_apply_outputs();
        pdu_send_telemetry();
    }
}

