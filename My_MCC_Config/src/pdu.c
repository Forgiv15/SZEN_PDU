#include "pdu.h"
#include "pdu_adc.h"
#include "pmbus.h"
#include "linear11.h"
#include "definitions.h"

/* TPS25990 PMBus addresses */
static const uint8_t tps_addr[8] =
{
    0x45, /* Hybrid */
    0x48, /* Vent1 */
    0x43, /* Vent2 */
    0x40, /* IGN */
    0x51, /* Fuel */
    0x41, /* WP1 */
    0x46, /* WP2 */
    0x50  /* 12V */
};

static bool check_voltage_all(void)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        uint16_t raw;
        if (pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_VOUT, &raw) != PMBUS_OK)
            return false;

        float v = linear11_to_float(raw);
        if (v < 11.0f)
            return false;
    }
    return true;
}

static bool check_power_all(void)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        uint16_t vraw, iraw, praw;

        if (pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_VOUT, &vraw) != PMBUS_OK)
            return false;
        if (pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_IOUT, &iraw) != PMBUS_OK)
            return false;
        if (pmbus_read_word(tps_addr[i], PMBUS_CMD_READ_PIN, &praw) != PMBUS_OK)
            return false;

        float v = linear11_to_float(vraw);
        float i = linear11_to_float(iraw);
        float p_calc = v * i;
        float p_meas = linear11_to_float(praw);

        if (p_meas < (p_calc * 0.5f)) /* sanity check */
            return false;
    }
    return true;
}

static bool check_fet_all(void)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        uint8_t status;

        pmbus_write_byte(tps_addr[i], PMBUS_CMD_OPERATION, 0x00);
        pmbus_write_byte(tps_addr[i], PMBUS_CMD_OPERATION, 0x80);

        if (pmbus_read_byte(tps_addr[i], PMBUS_CMD_STATUS_BYTE, &status) != PMBUS_OK)
            return false;

        if (status & (1u << 6)) /* FET_OFF bit */
            return false;
    }
    return true;
}

void PDU_Init(void)
{
    PDU_ADC_Init();

    GPIO_GLED_OutputEnable();
    GPIO_BLED_OutputEnable();
    GPIO_RLED_OutputEnable();

    GPIO_GLED_Set();
    GPIO_BLED_Set();
    GPIO_RLED_Set();
}

void PDU_RunChecks(void)
{
    bool v_ok = check_voltage_all();
    bool p_ok = check_power_all();
    bool f_ok = check_fet_all();

    /* Active-low LEDs */
    if (v_ok) GPIO_GLED_Clear();
    else GPIO_GLED_Toggle();

    if (p_ok) GPIO_BLED_Clear();
    else GPIO_BLED_Toggle();

    if (f_ok) GPIO_RLED_Clear();
    else GPIO_RLED_Toggle();
}
