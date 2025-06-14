/*!
 * @file    speed_test.c
 * @brief   Library for running speed tests.
 *
 * @author  Abdullah Almosalami @memphis242
 * @date    June 11, 2025
 * @copyright MIT License
 */

/* File Inclusions */
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "tmr_hal.h"
#include "uart_hal.h"
#include "speed_test.h"

// To allow usage in C++ code...
#ifdef __cplusplus
extern "C" {
#endif

/* Local Macro Definitions */

/* Datatypes */

/* Local Variables */
static bool StartCmdReceived;
static struct TmrHalHandle_S SpeedTestTimer;

/* Local Function Declarations */
static void SpeedTest_StartCmd_CB( struct HAL_UART_DataBuf_S * );

/* Meat of the Library */

/******************************************************************************/
void SpeedTest_Init(void)
{
   bool cb_registration_succeeded =
      HalUart_RegisterCallback(SpeedTestStartCmd, SpeedTest_StartCmd_CB);
   bool tmr_configured = TmrHal_Init(&SpeedTestTimer, NO_TIME_LIMIT);

   assert(cb_registration_succeeded);
   assert(tmr_configured);
}

/******************************************************************************/
void SpeedTest_Arm(void)
{
   TmrHal_ResumeTimer( &SpeedTestTimer );
}

/******************************************************************************/
void SpeedTest_Disarm(void)
{
   TmrHal_PauseTimer( &SpeedTestTimer );
}

/******************************************************************************/
uint32_t SpeedTest_GetTimerVal(void)
{
   return TmrHal_GetTimerVal( &SpeedTestTimer );
}

/******************************************************************************/
void SpeedTest_LogEntry(uint32_t elapsed_time)
{
   
}

/******************************************************************************/
void SpeedTest_SerialPrintLn(char * str)
{
   
}

/******************************************************************************/
bool SpeedTest_SerialPrintStats(void)
{
   
}

/******************************************************************************/
void SpeedTest_WaitForStartSignal(void)
{
   while ( StartCmdReceived == false );
   StartCmdReceived = false;
}

/******************************************************************************/


/* Local Function Definitions */

/**
 * @brief Callback invoked when a Speed Test Start Cmd has been received.
 *        Sets a flag to signal that this msg has been received.
 * @param msg Pointer to the HalUart_MsgData_S structure containing the UART message data.
 */
static void SpeedTest_StartCmd_CB( struct HalUart_MsgData_S * msg )
{
   assert( msg->id == 0x01 );

   StartCmdReceived = true;
}

#ifdef __cplusplus
}
#endif
