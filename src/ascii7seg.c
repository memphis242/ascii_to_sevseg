/**
 * @file ascii7seg.c
 * @brief Implementation of the ASCII to 7 Segment encoding API.
 *
 * @author Abdulla Almosalami (memphis242)
 * @date May 18, 2025
 * @copyright MIT License
 */

/* File Inclusions */
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "ascii7seg.h"

/* Local Macro Definitions */

/**
 * @brief Lookup table for 7-segment ASCII digit encodings.
 * 
 * @note This is made a macro because there will be repeated usage in Ascii7Seg_ConvertChar()
 *       for the various configurations of this module.
 *
 * This macro defines a static constant array, `NumLUT`, containing the segment encoding
 * for the digits 0 through 9 as displayed on a 7-segment display.
 *
 * Usage:
 *   NUM_LUT();
 *   // Access NumLUT[digit] to get the segment encoding for a digit (0-9).
 */
#define NUM_LUT()                                                                            \
   static const union Ascii7Seg_Encoding_U NumLUT[] =                                        \
   {                                                                                         \
      {  /* 0 */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 0 } },   \
      {  /* 1 */ .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 0, .f = 0, .g = 0 } },   \
      {  /* 2 */ .segments = { .a = 1, .b = 1, .c = 0, .d = 1, .e = 1, .f = 0, .g = 1 } },   \
      {  /* 3 */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 0, .g = 1 } },   \
      {  /* 4 */ .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 0, .f = 1, .g = 1 } },   \
      {  /* 5 */ .segments = { .a = 1, .b = 0, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 } },   \
      {  /* 6 */ .segments = { .a = 1, .b = 0, .c = 1, .d = 1, .e = 1, .f = 1, .g = 1 } },   \
      {  /* 7 */ .segments = { .a = 1, .b = 1, .c = 1, .d = 0, .e = 0, .f = 0, .g = 0 } },   \
      {  /* 8 */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 1 } },   \
      {  /* 9 */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 } }    \
   }

// Constant-like macros

// Function-like macros

/* Local Datatypes */

/* Private Function Prototypes */

/* Public API Implementations */

bool Ascii7Seg_ConvertChar( char ascii_char, union Ascii7Seg_Encoding_U * buf )
{
   if ( NULL == buf )
   {
      return false;
   }

#ifdef ASCII_7SEG_NUMS_ONLY

   if ( (ascii_char < '0') || (ascii_char > '9') )
   {
      // Invalid character
      return false;
   }

   assert( (ascii_char >= '0') && (ascii_char <= '9') );

#ifdef DONT_USE_LOOKUP_TABLE

   buf->segments.a = !( (ascii_char == '1') || (ascii_char == '4') );
   buf->segments.b = !( (ascii_char == '5') || (ascii_char == '6') );
   buf->segments.c = !(  ascii_char == '2');
   buf->segments.d = !( (ascii_char == '1') || (ascii_char == '4') || (ascii_char == '7') );
   buf->segments.e =  ( (ascii_char == '0') || (ascii_char == '2') || (ascii_char == '6') || (ascii_char == '8') );
   buf->segments.f = !( (ascii_char == '1') || (ascii_char == '2') || (ascii_char == '3') || (ascii_char == '7') );
   buf->segments.g = !( (ascii_char == '0') || (ascii_char == '1') || (ascii_char == '7') );

#else // Use a lookup table

   NUM_LUT();

   *buf = NumLUT[ ascii_char - '0' ];

#endif // DONT_USE_LOOKUP_TABLE


#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY) // if !ASCII_7SEG_NUMS_ONLY

   if ( (ascii_char < '0')  ||
        (
            (ascii_char > '9') &&   // letters start after the nums in ASCII
            !(
               (ascii_char == 'E') || (ascii_char == 'e') ||
               (ascii_char == 'R') || (ascii_char == 'r') ||
               (ascii_char == 'O') || (ascii_char == 'o')
            )
        )
      )
   {
      // Invalid character
      return false;
   }

   assert( ( (ascii_char >= '0') && (ascii_char <= '9') ) || 
           (ascii_char == 'E') || (ascii_char == 'e') ||
           (ascii_char == 'R') || (ascii_char == 'r') ||
           (ascii_char == 'O') || (ascii_char == 'o') );

#ifdef DONT_USE_LOOKUP_TABLE

   buf->segments.a = !( (ascii_char == '1') || (ascii_char == '4') || (ascii_char == 'r') || (ascii_char == 'o') );
   buf->segments.b = !( (ascii_char == '5') || (ascii_char == '6') || (ascii_char == 'E') || (ascii_char == 'r') || (ascii_char == 'o') );
   buf->segments.c = !( (ascii_char == '2') || ( (ascii_char > '9') && (ascii_char != 'o') && (ascii_char != 'O') ) ); // Letters are all greater than '9'
   buf->segments.d = !( (ascii_char == '1') || (ascii_char == '4') || (ascii_char == '7') || (ascii_char == 'R') || (ascii_char == 'r') );
   buf->segments.e =  ( (ascii_char == '0') || (ascii_char == '2') || (ascii_char == '6') || (ascii_char == '8') || (ascii_char > '9') );
   buf->segments.f = !( (ascii_char == '1') || (ascii_char == '2') || (ascii_char == '3') || (ascii_char == '7') || (ascii_char == 'r') || (ascii_char == 'o') );
   buf->segments.g = !( (ascii_char == '0') || (ascii_char == '1') || (ascii_char == '7') || (ascii_char == 'R') || (ascii_char == 'O') || (ascii_char == 'o') );

#else // Use a lookup table

   // Make two separate lookup tables so I don't have to repeat the numeric lookup table outside of the NUM_LUT macro.
   // This adds an if statement but I think that's worth it because of the easier time hashing.
   NUM_LUT();
   static const union Ascii7Seg_Encoding_U ErrorLUT[] =
   {                                                                                      
      {  /* e */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 0 } },
      {  /* E */ .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 0, .f = 0, .g = 0 } },
      {  /* r */ .segments = { .a = 1, .b = 1, .c = 0, .d = 1, .e = 1, .f = 0, .g = 1 } },
      {  /* R */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 0, .g = 1 } },
      {  /* o */ .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 0, .f = 1, .g = 1 } },
      {  /* O */ .segments = { .a = 1, .b = 0, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 } }
   };

   if ( ascii_char > '9' )
   {
      // See "Notes for Hashing.txt" file at root of repo
      uint8_t hash = ((((uint8_t)ascii_char & 0x3) - 1) << 1) + (((uint8_t)ascii_char & 0x20) > 0);
      *buf = ErrorLUT[hash];
   }
   else
   {
      *buf = NumLUT[ ascii_char - '0' ];
   }

#endif // DONT_USE_LOOKUP_TABLE


#else // Full range of supported characters

#ifdef DONT_USE_LOOKUP_TABLE

#else

#endif // DONT_USE_LOOKUP_TABLE

#endif // endif for macros that limit range of representable values

   // If we've reached here, we've successfully encoded the character.
   return true;
}


bool Ascii7Seg_ConvertWord( const char * str,
                            size_t str_len,
                            union Ascii7Seg_Encoding_U * buf )
{
   if ( (NULL == str) || (NULL == buf) )
   {
      return false;
   }

   bool word_converted = false;
   unsigned int iterations = 0;
   while ( (str[iterations] != '\0') && (iterations < str_len) )
   {
      word_converted = Ascii7Seg_ConvertChar( str[iterations],
                                              &buf[iterations] );
      if ( !word_converted )
      {
         // Character failed to convert
         break;
      }

      iterations++;
   }

   return word_converted;
}
