/**
 * @file speed_test.h
 * @brief API needed for a speed test, including a logger and a serial printer.
 *
 * @author Abdulla Almosalami (memphis242)
 * @date June 11, 2025
 * @copyright MIT License
 */

#ifndef SPEED_TEST_H
#define SPEED_TEST_H

/* File Inclusions */
#include <stdbool.h>
#include <stdint.h>
#include "tmr_hal.h"

/* Public Macro Definitions */
#define SPEED_TEST_TIMER_COUNTS_TO_US(elapsed_time)  \
           (elapsed_time * TMR_TICKS_TO_US)

/* Public Datatypes */

/* Public API */

// To allow usage in C++ code...
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the SpeedTest module (should be done prior to any usage)
 */
void SpeedTest_Init(void);

/**
 * @brief Sets the SpeedTest ready for a fresh logging session
 */
void SpeedTest_Arm(void);

/**
 * @brief Stops the SpeedTest from any more logging - undone by SpeedTest_Arm
 */
void SpeedTest_Disarm(void);

/**
 * @brief Get the current speed test timer value
 * @return 32-bit unsigned integer representing the current timer value
 */
uint32_t SpeedTest_GetTimerVal(void);

/**
 * @brief Logs a (presumably) elapsed time value
 * @param 32-bit unsigned integer representing the elapsed time of a test cycle
 */
void SpeedTest_LogEntry(uint32_t elapsed_time);

/**
 * @brief Prints the string passed in (no formatting) and a newline at the end
 * @param String to print out
 */
void SpeedTest_SerialPrintLn(char * str);

/**
 * @brief Print out the statistics of the last logging session
 * @note This will trigger a statistics computation on the last logging session
 *       if this was not already done.
 * @note The speed test should be disarmed using SpeedTest_Disarm prior to
 *       calling this function, or else it will fail.
 * @param String to print out
 * @return true if successful | false otherwise
 */
bool SpeedTest_SerialPrintStats(void);

/**
 * @brief Spins (waits indefinitely) until a valid start signal is received
 */
void SpeedTest_WaitForStartSignal(void);

#ifdef __cplusplus
}
#endif

#endif // SPEED_TEST_H
