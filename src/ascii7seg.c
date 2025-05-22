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

// Constant-like macros

// Function-like macros

/* Local Datatypes */

/* Private Function Prototypes */

/* Public API Implementations */

bool Ascii7Seg_ConvertChar( char ascii_char, union Ascii7Seg_Encoding_U * buf )
{
   #ifdef ASCII_7SEG_NUMS_ONLY

   #ifdef DONT_USE_LOOKUP_TABLE
   
   #else

   #endif // DONT_USE_LOOKUP_TABLE

   #elif ASCII_7SEG_NUMS_AND_ERR_ONLY

   #ifdef DONT_USE_LOOKUP_TABLE
   
   #else

   #endif // DONT_USE_LOOKUP_TABLE

   #else

   #ifdef DONT_USE_LOOKUP_TABLE
   
   #else

   #endif // DONT_USE_LOOKUP_TABLE

   #endif // endif for macros that limit range of representable values
}

bool Ascii7Seg_ConvertWord( const char * str,
                            size_t str_len,
                            union Ascii7Seg_Encoding_U * buf )
{
   if ( (NULL == str) || (NULL == buf) )
   {
      return false;
   }

#ifndef ASCII_7SEG_MAX_WORD_LEN
#define ASCII_7SEG_MAX_WORD_LEN 100
#endif
   bool word_converted = false;
   unsigned int iterations = 0;
   while ( (str[iterations] != '\0') && (iterations < ASCII_7SEG_MAX_WORD_LEN) )
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
