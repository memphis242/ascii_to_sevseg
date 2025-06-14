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
#include "speed_test_cfg.h"

// To allow usage in C++ code...
#ifdef __cplusplus
extern "C" {
#endif

/* Local Macro Definitions */
#define US_MAX UINT32_MAX

/* Datatypes */
typedef uint32_t us_t;

/* Local Variables */
static bool StartCmdReceived;
static bool TestArmed;

static us_t SpeedTestLog[SPEED_TEST_ITERATIONS_PER_FCN_TESTER];
static size_t SpeedTestLogIdx;

/* Local Function Declarations */
static void SpeedTest_StartCmd_CB( struct HAL_UART_DataBuf_S * );

/* Meat of the Library */

/******************************************************************************/
void SpeedTest_Init(void)
{
   bool cb_registration_succeeded =
      HalUart_RegisterCallback(SpeedTestStartCmd, SpeedTest_StartCmd_CB);
   bool tmr_configured = TmrHal_Init();

   assert(cb_registration_succeeded);
   assert(tmr_configured);
}

/******************************************************************************/
void SpeedTest_Arm(void)
{
   TestArmed = true;
   SpeedTestLogIdx = 0;
}

/******************************************************************************/
void SpeedTest_Disarm(void)
{
   TestArmed = false;
}

/******************************************************************************/
us_t SpeedTest_GetTimerVal(void)
{
   assert(TestArmed);

   return TmrHal_GetTimerVal();
}

/******************************************************************************/
void SpeedTest_LogEntry(us_t elapsed_time)
{
   assert(TestArmed);

   SpeedTestLog[SpeedTestLogIdx] = elapsed_time;
   SpeedTestLogIdx++;

   assert(SpeedTestLogIdx < SPEED_TEST_ITERATIONS_PER_FCN_TESTER);
}

/******************************************************************************/
void SpeedTest_SerialPrintLn(char * str)
{
   assert(!TestArmed);

   // TODO: SerialPrintLn
}

/******************************************************************************/
bool SpeedTest_SerialPrintStats(void)
{
   assert(!TestArmed);

   // Compute stats
   uint64_t running_sum = 0;
   us_t avg = 0;
   us_t std_dev = 0;
   int16_t variance_diffs[SPEED_TEST_ITERATIONS_PER_FCN_TESTER];
   us_t min = US_MAX;
   us_t max = 0;
   // First the avg, min, and max
   for ( size_t i = 0; i < (SpeedTestLogIdx + 1); i++ )
   {
      us_t log_entry = SpeedTestLog[i];
      running_sum += log_entry;
      if ( min > log_entry )  min = log_entry;
      if ( max < log_entry )  max = log_entry;
   }
   avg = (us_t)( running_sum / (SpeedTestLogIdx + 1) );
   // Now the standard deviation
   running_sum = 0;
   for ( size_t i = 0; i < (SpeedTestLogIdx + 1); i++ )
   {
      variance_diffs[i] = (int16_t)(SpeedTestLog[i] - avg);
      variance_diffs[i] *= variance_diffs[i];
      running_sum += variance_diffs[i];
   }
   std_dev = isqrt( running_sum / (SpeedTestLogIdx + 1) );

   // Transmit the stats over our serial port
   // TODO: Transmit the stats over our serial port

   return false;
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
