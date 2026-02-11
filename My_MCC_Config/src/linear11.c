#include "linear11.h"

float linear11_to_float(uint16_t word)
{
    /* Extract signed exponent (5-bit) */
    int8_t exp = (int8_t)((word >> 11) & 0x1F);
    if (exp & 0x10) {
        exp |= (int8_t)0xE0; /* sign extend */
    }

    /* Extract signed mantissa (11-bit) */
    int16_t mant = (int16_t)(word & 0x07FF);
    if (mant & 0x0400) {
        mant |= (int16_t)0xF800; /* sign extend */
    }

    float value = (float)mant;
    while (exp > 0) {
        value *= 2.0f;
        exp--;
    }
    while (exp < 0) {
        value *= 0.5f;
        exp++;
    }
    return value;
}
