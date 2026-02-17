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
    /* Initialize ADC for IMON readings */
    PDU_ADC_Init();

    /* Configure LED GPIOs as outputs */
    GPIO_GLED_OutputEnable();
    GPIO_BLED_OutputEnable();
    GPIO_RLED_OutputEnable();

    /* LEDs are active-low, start with all OFF (Set = LED off) */
    GPIO_GLED_Set();
    GPIO_BLED_Set();
    GPIO_RLED_Set();
}

void PDU_RunChecks(void)
{
    bool v_ok = check_voltage_all();
    bool p_ok = check_power_all();
    bool f_ok = check_fet_all();

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