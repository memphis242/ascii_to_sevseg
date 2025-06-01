/**
 * @file ascii7seg_config.h
 * @brief Configuration macros to modify how this library will execute its functionality.
 *
 * By default, the library will be lazy and use a lookup table to perform the
 * encoding and the primary interface datatype Ascii7Seg_Encoding_U will _not_
 * be bitpacked. It will also have the following range of valid encodable
 * characters (aka the Default Encodable Range):
 *    - 0-9
 *    - Special Characters: [ ] _ - | =
 *    - a-z (not every character will be beautiful)
 *    - A-Z (not every character will be beautiful)
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
#ifdef ASCII_7SEG_BIT_PACK
#define ASCII_7SEG_BIT_PACK_MASK 0x7Fu // lower 7 bits

/**
 * Define this macro SPECIAL_PACKING_PRAGMA_KEYWORD if you are using a
 * compiler that is not GCC, clang, or MSVC and need to specify a packing
 * pragma that differs from those three compilers.
 *
 * For example, the Microchip XC8 compiler specifies packing using "__pack"
 * placed before the type or variable declaration.
 *
 * This macro is not fool-proof and is placed before the struct keyword in
 * ascii7seg.h's definition of the union Ascii7Seg_Encoding_U type.
 * 
 * Also, if you don't define this macro, everything should still be fine. You
 * just won't get the extra degree of force on the compiler to pack the bit-field'd
 * struct in Ascii7Seg_Encoding_U.
 */
#define SPECIAL_PACKING_PRAGMA_KEYWORD // e.g., __pack for the Microchip XC8 compiler

#endif // ASCII_7SEG_BIT_PACK

//! Uncomment to enforce computation of encoding instead of lookup (to save mem)
//#define ASCII_7SEG_DONT_USE_LOOKUP_TABLE


/************************ Config Macros to Limit Range ************************/
// NOTE! Only one of the below macros will take effect.
// NOTE! If you did not uncomment any of the below macros, the Default Encodable
//       Range is assumed (see file header comment).

//! Uncomment to narrow down the set of characters to convert to only the digits 0-9 (saves space and computation time)
//#define ASCII_7SEG_NUMS_ONLY

#ifndef ASCII_7SEG_NUMS_ONLY  // Do not remove this #ifndef construct!
//! Uncomment to narrow down the set of characters to convert to only the digits 0-9, E, and r (saves space and computation time)
//#define ASCII_7SEG_NUMS_AND_ERROR_ONLY
#endif // ASCII_7SEG_NUMS_ONLY

#endif // ASCII_7SEG_CFG_H_
