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

#ifdef DONT_USE_LOOKUP_TABLE

   buf->segments.a = !( (ascii_char == '1') || (ascii_char == '4') );
   buf->segments.b = !( (ascii_char == '5') || (ascii_char == '6') );
   buf->segments.c = !(  ascii_char == '2');
   buf->segments.d = !( (ascii_char == '1') || (ascii_char == '4') || (ascii_char == '7') );
   buf->segments.e =  ( (ascii_char == '0') || (ascii_char == '2') || (ascii_char == '6') || (ascii_char == '8') );
   buf->segments.f = !( (ascii_char == '1') || (ascii_char == '2') || (ascii_char == '3') || (ascii_char == '7') );
   buf->segments.g = !( (ascii_char == '0') || (ascii_char == '1') || (ascii_char == '7') );

#else

   static const union Ascii7Seg_Encoding_U NumLUT[] =
   {
      {  /* 0 */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 0 } },
      {  /* 1 */ .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 0, .f = 0, .g = 0 } },
      {  /* 2 */ .segments = { .a = 1, .b = 1, .c = 0, .d = 1, .e = 1, .f = 0, .g = 1 } },
      {  /* 3 */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 0, .g = 1 } },
      {  /* 4 */ .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 0, .f = 1, .g = 1 } },
      {  /* 5 */ .segments = { .a = 1, .b = 0, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 } },
      {  /* 6 */ .segments = { .a = 1, .b = 0, .c = 1, .d = 1, .e = 1, .f = 1, .g = 1 } },
      {  /* 7 */ .segments = { .a = 1, .b = 1, .c = 1, .d = 0, .e = 0, .f = 0, .g = 0 } },
      {  /* 8 */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 1 } },
      {  /* 9 */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 } }
   };

   *buf = NumLUT[ ascii_char - '0' ];

#endif // DONT_USE_LOOKUP_TABLE


#elif ASCII_7SEG_NUMS_AND_ERR_ONLY // if !ASCII_7SEG_NUMS_ONLY

#ifdef DONT_USE_LOOKUP_TABLE

#else

#endif // DONT_USE_LOOKUP_TABLE

#else

#ifdef DONT_USE_LOOKUP_TABLE

#else

#endif // DONT_USE_LOOKUP_TABLE

#endif // endif for macros that limit range of representable values

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
