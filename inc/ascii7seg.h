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

/* Public Macro Definitions */

//! Uncomment to use bit-packing for the Ascii7Seg_Encoding_S struct
//#define ASCII_7SEG_BIT_PACK

//! Uncomment to enforce computation of encoding instead of lookup (to save mem)
//#define DONT_USE_LOOKUP_TABLE

/* Public Datatypes */

/**
 * @brief Structure representing the state of a 7-segment display.
 *
 * This structure holds the on/off state for each segment (A-G) of a 7-segment
 * display. The representation of each segment can be either as individual bits
 * (bit-packed) or as separate bool values, depending on whether ASCII_7SEG_BIT_PACK
 * is defined.
 */
struct Ascii7Seg_Encoding_S
{
#ifdef ASCII_7SEG_BIT_PACK
   unsigned int a : 1;
   unsigned int b : 1;
   unsigned int c : 1;
   unsigned int d : 1;
   unsigned int e : 1;
   unsigned int f : 1;
   unsigned int g : 1;
   unsigned int reserved : 1; // UNUSED. Helps ensure (but still not a guarantee) that the compiler stores all these bits in a single byte for tighter storage.
#else
   bool a;
   bool b;
   bool c;
   bool d;
   bool e;
   bool f;
   bool g;
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
 * This function takes a single ASCII character as input and fills the provided
 * structure with the 7-segment display drive signals required to display the
 * character.
 * 
 * @note Supported Characters: (not every ASCII character!)
 *  0-9
 *  [, ], _, -, |, =,
 *  a-z (not every character will be beautiful)
 *  A-Z (not every character will be beautiful)
 * 
 * @note If the character is not supported, then the encoding will be set to all
 *       segments off and the function will return false.
 *
 * @param[in]  ascii_char The ASCII character to convert.
 * @param[out] buf   Pointer to the structure to store the 7-segment encoding.
 * 
 * @return true if the conversion was successful; false otherwise.
 */
bool Ascii7Seg_ConvertChar( char ascii_char, struct Ascii7Seg_Encoding_S * buf );

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
                            struct Ascii7Seg_Encoding_S * buf );


#ifdef __cplusplus
}
#endif

#endif // ASCII_7SEG_H_
