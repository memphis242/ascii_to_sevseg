/**
 * @file ascii7seg_config.h
 * @brief Configuration macros to modify how this library will behave and its
 *        interface.
 *
 * By default, the library will be lazy and use a lookup table to perform the
 * encoding and the primary interface datatype Ascii7Seg_Encoding_U will _not_
 * be bitpacked.
 * 
 * @note Comment/uncomment the macros present here to change which sections of
 *       code are visible to the compiler.
 *
 * @author Abdulla Almosalami (memphis242)
 * @date May 20, 2025
 * @copyright MIT License
 */

#ifndef ASCII_7SEG_CFG_H_
#define ASCII_7SEG_CFG_H_

/* Public Macro Definitions */

//! Uncomment to use bit-packing for the Ascii7Seg_Encoding_S struct
//#define ASCII_7SEG_BIT_PACK

//! Uncomment to enforce computation of encoding instead of lookup (to save mem)
//#define DONT_USE_LOOKUP_TABLE

//! Uncomment to narrow down the set of characters to convert to only the digits 0-9 (saves space and computation time)
//#define ASCII_7SEG_NUMS_ONLY

//! Uncomment to narrow down the set of characters to convert to only the digits 0-9, E, and r (saves space and computation time)
//#define ASCII_7SEG_NUMS_AND_ERR_ONLY

#endif // ASCII_7SEG_CFG_H_
