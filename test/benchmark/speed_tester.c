/*!
 * @file    speed_tester.c
 * @brief   Benchmark harness that calls this library's functions and logs
 *          execution speed.
 *
 * @author  Abdullah Almosalami @memphis242
 * @date    June 11, 2025
 * @copyright MIT License
 */

/* File Inclusions */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include "ascii7seg.h"
#include "ascii7seg_config.h"
#include "speed_test.h"

/* Local Macro Definitions */
#define TEST_ITERATIONS 100
#define RUN_TEST(f)                                                            \
   uint32_t tmr_start = 0;                                                     \
   uint32_t tmr_end = 0;                                                       \
   uint32_t elapsed_time = 0;                                                  \
   SpeedTest_Arm();                                                            \
   for ( size_t i = 0; i < TEST_ITERATIONS; i++ )                              \
   {                                                                           \
      tmr_start = SpeedTest_GetTimerVal();                                     \
      f();                                                                     \
      tmr_end = SpeedTest_GetTimerVal();                                       \
      if ( tmr_end <= tmr_start )                                              \
      {                                                                        \
         elapsed_time = (UINT32_MAX - tmr_start) + tmr_end;                    \
      }                                                                        \
      else                                                                     \
      {                                                                        \
         elapsed_time = tmr_end - tmr_start;                                   \
      }                                                                        \
      elapsed_time = SPEED_TEST_TIMER_COUNTS_TO_US(elapsed_time);              \
      SpeedTest_LogEntry(elapsed_time);                                        \
   }                                                                           \
   SpeedTest_Disarm();                                                         \
   SpeedTest_SerialPrintLn(#f);                                                \
   SpeedTest_SerialPrintStats();

/* Datatypes */

/* Local Variables */

/* Forward Function Declarations */

void MCUSetup(void);

void FcnTester_Ascii7Seg_ConvertChar(void);
void FcnTester_Ascii7Seg_ConvertWord(void);
void FcnTester_Ascii7Seg_ConvertNum(void);
void FcnTester_Ascii7Seg_IsSupportedChar(void);

/* Meat of the Program */

int main(void)
{
   MCUSetup();

   while(1)
   {
      SpeedTest_WaitForStartSignal();
      RUN_TEST(FcnTester_Ascii7Seg_ConvertChar);

      SpeedTest_WaitForStartSignal();
      RUN_TEST(FcnTester_Ascii7Seg_ConvertWord);

      SpeedTest_WaitForStartSignal();
      RUN_TEST(FcnTester_Ascii7Seg_ConvertNum);

      SpeedTest_WaitForStartSignal();
      RUN_TEST(FcnTester_Ascii7Seg_IsSupportedChar);
   }
}
