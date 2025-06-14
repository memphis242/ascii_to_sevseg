/**
 * @file uart_hal.h
 * @brief HAL API for a µC's UART port.
 *
 * @author Abdulla Almosalami (memphis242)
 * @date June 13, 2025
 * @copyright MIT License
 */

#ifndef UART_HAL_H
#define UART_HAL_H

/* File Inclusions */
#include <stdbool.h>
#include <stdint.h>

// To allow usage in C++ code...
#ifdef __cplusplus
extern "C" {
#endif

/* Public Macro Definitions */

/* Public Datatypes */

typedef uint8_t id_t;

struct HalUart_MsgData_S
{
   id_t id;
   uint8_t * buf;
   size_t len;
};

#define UART_MSG_RX(enum, id, num)  enum,

enum HalUart_RxMsg_E
{
#include "uart_msg_list.h"
   NUM_OF_UART_RX_MSGS
};

#undef UART_MSG_RX

typedef void (*HalUart_RxMsgCB_F)(struct HalUart_DataBuf_S *);

/* Public API */

/**
 * @brief Register a callback function for a particular RX msg
 * @param enum HalUart_RxMsg_E - The RX msg this callback will be called for
 * @param HalUart_RxMsgCB_F - The callback that will be called
 * @return true if registration was successful | false otherwise (e.g., invalid
 *         msg or a callback already registered)
 */
bool HalUart_RegisterCallback( enum HalUart_RxMsg_E, HalUart_RxMsgCB_F );


#ifdef __cplusplus
}
#endif

#endif // UART_HAL_H
