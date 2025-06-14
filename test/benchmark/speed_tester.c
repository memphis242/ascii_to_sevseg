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

//! Number of test cycle iterations for RUN_TEST to do
#define TEST_ITERATIONS 100

//! Macro function to run a test, including all the TEST_ITERATIONS cycles
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

/* Extern Function Declarations */

extern void MCUSetup(void);

/* Local Function Declarations */

static void FcnTester_Ascii7Seg_ConvertChar(void);
static void FcnTester_Ascii7Seg_ConvertWord(void);
static void FcnTester_Ascii7Seg_ConvertNum(void);
static void FcnTester_Ascii7Seg_IsSupportedChar(void);

/* Meat of the Program */

/**
 * @brief main function for running all the tests and reporting the data
 */
int main(void)
{
   MCUSetup();
   SpeedTest_Init();

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

/* Local Function Definitions */

static void FcnTester_Ascii7Seg_ConvertChar(void)
{
   union Ascii7Seg_Encoding_U buf;
   for ( int16_t c = CHAR_MIN; c <= CHAR_MAX; c++ )
   {
      (void)Ascii7Seg_ConvertChar((char)c, &buf);
   }
}

static void FcnTester_Ascii7Seg_ConvertWord(void)
{
   union Ascii7Seg_Encoding_U buf[20];
   (void)Ascii7Seg_ConvertWord("ERROR", 20, buf);
   (void)Ascii7Seg_ConvertWord("error", 20, buf);
   (void)Ascii7Seg_ConvertWord("SUCCESS", 20, buf);
   (void)Ascii7Seg_ConvertWord("success", 20, buf);
   (void)Ascii7Seg_ConvertWord("FAIL", 20, buf);
   (void)Ascii7Seg_ConvertWord("fail", 20, buf);
   (void)Ascii7Seg_ConvertWord("HELLO WORLD!", 20, buf);
   (void)Ascii7Seg_ConvertWord("hello world!", 20, buf);
}

static void FcnTester_Ascii7Seg_ConvertNum(void)
{
   union Ascii7Seg_Encoding_U buf[3];
   for ( uint16_t i = 100; i < 1000; i++ )
   {
      (void)Ascii7Seg_ConvertNum(i, buf, 3);
   }
}

static void FcnTester_Ascii7Seg_IsSupportedChar(void)
{
   for ( int16_t c = CHAR_MIN; c <= CHAR_MAX; c++ )
   {
      (void)Ascii7Seg_IsSupportedChar((char)c);
   }
}
