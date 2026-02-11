#ifndef PDU_H
#define PDU_H

#include <stdbool.h>
//#include <stdint.h>

typedef enum
{
    PDU_OK = 0,
    PDU_FAULT
} pdu_result_t;

void PDU_Init(void);
void PDU_RunChecks(void);

#endif /* PDU_H */
