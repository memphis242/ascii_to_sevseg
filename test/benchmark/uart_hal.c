/*!
 * @file    uart_hal.c
 * @brief   Implementation of the UART HAL API.
 *
 * @author  Abdullah Almosalami @memphis242
 * @date    June 13, 2025
 * @copyright MIT License
 */

/* File Inclusions */
#include <stdbool.h>
#include <stdint.h>
#include "uart_hal.h"
#include "uart_hal_cfg.h"

// To allow usage in C++ code...
#ifdef __cplusplus
extern "C" {
#endif

/* Local Macro Definitions */

/* Datatypes */

struct MsgCfg_S
{
   HalUart_RxMsgCB_F cb;
   id_t id;
};

/* Local Variables */
static struct MsgCfg_S RxMsgCfgTable[NUM_OF_UART_RX_MSGS];
static struct HalUart_MsgData_S RxMsgPool[UART_HAL_RX_MSG_BUF_POOL_SIZE];

/* Local Function Declarations */

/* Meat of the Library */

/******************************************************************************/
bool HalUart_RegisterCallback( enum HalUart_RxMsg_E msg, HalUart_RxMsgCB_F cb )
{
   if ( (msg >= NUM_OF_UART_RX_MSGS) ||
        (NULL == cb) ||
        (RxMsgCfgTable[msg].cb != NULL) )
   {
      return false;
   }

   RxMsgCfgTable[msg].cb = cb;
}

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/

#ifdef __cplusplus
}
#endif
