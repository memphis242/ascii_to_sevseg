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
   static const union Ascii7Seg_Encoding_U NumLUT[] =
   {
      {  // 0
         .segment =
         {
                  .a = 1;
            .f = 1;     .b = 1;
                  .g = 0;
            .e = 1;     .c = 1;
                  .d = 1;
         },
      }
      {  // 1
         .segment =
         {
                  .a = 0;
            .f = 0;     .b = 1;
                  .g = 0;
            .e = 0;     .c = 1;
                  .d = 0;
         }
      },
      {  // 2
         .segment =
         {
               .a = 1;
         .f = 0;     .b = 1;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 1;
         }
      },
      {  // 3
         .segment =
         {
                  .a = 1;
            .f = 0;     .b = 1;
                  .g = 1;
            .e = 0;     .c = 1;
                  .d = 1;
         }
      },
      {  // 4
         .segment =
         {
                  .a = 0;
            .f = 1;     .b = 1;
                  .g = 1;
            .e = 0;     .c = 1;
                  .d = 0;
         }
      },
      {  // 5
         .segment =
         {
                  .a = 1;
            .f = 1;     .b = 0;
                  .g = 1;
            .e = 0;     .c = 1;
                  .d = 1;
         }
      },
      {  // 6
         .segment =
         {
                  .a = 1;
            .f = 1;     .b = 0;
                  .g = 1;
            .e = 1;     .c = 1;
                  .d = 1;
         }
      },
      {  // 7
         .segment =
         {
                  .a = 1;
            .f = 0;     .b = 1;
                  .g = 0;
            .e = 0;     .c = 1;
                  .d = 0;
         }
      },
      {  // 8
         .segment =
         {
                  .a = 1;
            .f = 1;     .b = 1;
                  .g = 1;
            .e = 1;     .c = 1;
                  .d = 1;
         }
      },
      {  // 9
         .segment =
         {
                  .a = 1;
            .f = 1;     .b = 1;
                  .g = 1;
            .e = 0;     .c = 1;
                  .d = 1;
         }
      }
   }


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
