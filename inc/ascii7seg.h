/**
 * @file ascii7seg.h
 * @brief Convert an ASCII character to a 7-segment encoding.
 *
 * @author Abdulla Almosalami (memphis242)
 * @date May 18, 2025
 * @copyright MIT License
 */

#ifndef ASCII_7SEG_H_
#define ASCII_7SEG_H_

/* File Inclusions */
#include <stdbool.h>
#include <stdint.h>
#include "ascii7seg_config.h"

/* Public Macro Definitions */

/* Public Datatypes */

/**
 * @brief Union representing the state of a 7-segment display encoding.
 *
 * This union provides two ways to access the state of each segment (A-G) in a 7-segment display:
 * - As individual segment fields (either bit-packed or as separate bools, depending on whether ASCII_7SEG_BIT_PACK is defined).
 * - As a single value (either an unsigned integer for bit-packed, or a bool array for non-bit-packed).
 *
 * When ASCII_7SEG_BIT_PACK is defined:
 *   - Each segment (a-g) is represented as a single bit within a struct, allowing compact storage in one byte.
 *   - The 'reserved' bit encourages the compiler to use one byte to store all 8 bitfield members.
 *   - The entire encoding can also be accessed as an unsigned integer via 'encoding_as_val'.
 *
 * When ASCII_7SEG_BIT_PACK is not defined:
 *   - Each segment is represented as a separate bool field.
 *   - The entire encoding can also be accessed as a bool array via 'encoding_as_val'.
 *
 * This design provides the user flexibility in the way they want to represent the 7-segment display states.
 */
union Ascii7Seg_Encoding_U
{
   struct
   {
   #ifdef ASCII_7SEG_BIT_PACK
      unsigned a : 1;
      unsigned b : 1;
      unsigned c : 1;
      unsigned d : 1;
      unsigned e : 1;
      unsigned f : 1;
      unsigned g : 1;
      unsigned reserved : 1; // UNUSED. Helps encourage the compiler to store all these bits in a single byte for tighter storage.
   #else
      bool a;
      bool b;
      bool c;
      bool d;
      bool e;
      bool f;
      bool g;
   #endif
   } segments;

   #ifdef ASCII_7SEG_BIT_PACK
   unsigned encoding_as_val;
   #else
   bool encoding_as_val[7];
   #endif
};

/* Public API */

// To allow usage in C++ code...
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Converts an ASCII character to its corresponding 7-segment display
 *        encoding.
 *
 * This function takes a single ASCII character as input and encode it into the
 * Ascii7Seg_Encoding_U structure that represent the 7-segment display drive
 * signals required to display the character.
 * 
 * @note Supported Characters (can be limited by the macros in
 *       ascii7seg_config.h):
 *    0-9
 *    [, ], _, -, |, =,
 *    a-z (not every character will be beautiful)
 *    A-Z (not every character will be beautiful)
 * 
 * @note If the character is not supported, then the encoding will be set to all
 *       segments off and the function will return false.
 *
 * @param[in]  ascii_char The ASCII character to convert.
 * @param[out] buf   Pointer to the structure to store the 7-segment encoding.
 * 
 * @return true if the conversion was successful; false otherwise.
 */
bool Ascii7Seg_ConvertChar( char ascii_char, union Ascii7Seg_Encoding_U * buf );

/**
 * @brief Converts an ASCII string to its 7-segment display encoding.
 *
 * This function takes an input ASCII string and converts each character
 * into its corresponding 7-segment display encoding, storing the result
 * in the provided buffer.
 *
 * @param[in]  str      Pointer to the input ASCII string.
 * @param[in]  str_len  Length of the input string to convert.
 * @param[out] buf      Pointer to the buffer where the 7-segment encodings will be stored.
 *
 * @return true if the conversion was successful for all characters; false otherwise.
 */
bool Ascii7Seg_ConvertWord( const char * str,
                            size_t str_len,
                            union Ascii7Seg_Encoding_U * buf );


#ifdef __cplusplus
}
#endif

#endif // ASCII_7SEG_H_
