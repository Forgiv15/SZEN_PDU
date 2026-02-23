/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "peripheral/port/plib_port.h"
#include "pdu.h"


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
  uint32_t tick_count = 0U;
  uint32_t last_100ms_tick = 0U;
  uint32_t last_1s_tick = 0U;
  uint32_t last_500ms_tick = 0U;

    /* Initialize all modules */
    SYS_Initialize( NULL );
    SYSTICK_TimerStart();

  PDU_Init();

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();

    if (SYSTICK_TimerPeriodHasExpired()) {
      tick_count++;
    }

#if (PDU_CAN_DEBUG_ONLY_MODE == 1U)
    if ((tick_count - last_500ms_tick) >= 500U)
    {
      last_500ms_tick += 500U;
      (void)PDU_CANSendHeartbeat();
    }
#else
    if ((tick_count - last_1s_tick) >= 1000U)
    {
      last_1s_tick += 1000U;
      (void)PDU_CANSendHeartbeat();
    }

    if ((tick_count - last_100ms_tick) >= 100U)
    {
      last_100ms_tick += 100U;

      PDU_RunChecks();
      PDU_PollAndSendTelemetry();
    }
#endif
  }

    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

