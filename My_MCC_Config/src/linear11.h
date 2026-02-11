#ifndef LINEAR11_H
#define LINEAR11_H

#include <stdint.h>

/* Decode PMBus Linear11 format into float */
float linear11_to_float(uint16_t word);

#endif /* LINEAR11_H */
