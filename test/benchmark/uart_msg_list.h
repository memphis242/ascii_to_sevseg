/**
 * @file uart_msg_list.h
 * @brief X-macro list of UART messages to be received and transmitted.
 *
 * @author Abdulla Almosalami (memphis242)
 * @date June 13, 2025
 * @copyright MIT License
 */

#ifndef UART_MSG_LIST_H
#define UART_MSG_LIST_H

//           Msg Enum               Msg Header
UART_MSG_RX( SpeedTestStartCmd,     0x01        )

UART_MSG_TX( SpeedTestLogData,      0x10        )

#endif // UART_MSG_LIST_H
