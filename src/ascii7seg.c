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
#include <ctype.h>
#include <limits.h>
#include "ascii7seg.h"
#include "ascii7seg_config.h"

/* Local Macro Definitions */

// Constant-like macros

// Function-like macros

/* Local Datatypes */

/* Local Data */

#if !defined(ASCII_7SEG_NUMS_ONLY) && !defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)

/**
 * MasterLUT is a lookup table (LUT) containing the 7-segment display encodings
 * for all supported ASCII characters.
 *
 * The table is indexed by the ASCII value of the character, allowing for fast
 * retrieval of the segment encoding for any character in the supported range,
 * and removing the need for a hash. Hypothetically, a clever-er hash function
 * can condense down this table, but I'm yet to come up with one.
 */
static const union Ascii7Seg_Encoding_U MasterLUT[ CHAR_MAX + 1 ] =
{
   [(uint8_t)'0'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)'1'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 0, .f = 0, .g = 0 }, },
   [(uint8_t)'2'] = { .segments = { .a = 1, .b = 1, .c = 0, .d = 1, .e = 1, .f = 0, .g = 1 }, },
   [(uint8_t)'3'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 0, .g = 1 }, },
   [(uint8_t)'4'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 0, .f = 1, .g = 1 }, },
   [(uint8_t)'5'] = { .segments = { .a = 1, .b = 0, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 }, },
   [(uint8_t)'6'] = { .segments = { .a = 1, .b = 0, .c = 1, .d = 1, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'7'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 0, .e = 0, .f = 0, .g = 0 }, },
   [(uint8_t)'8'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'9'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 }, },
   [(uint8_t)'('] = { .segments = { .a = 1, .b = 0, .c = 0, .d = 1, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)')'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 0, .g = 0 }, },
   [(uint8_t)'['] = { .segments = { .a = 1, .b = 0, .c = 0, .d = 1, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)']'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 0, .g = 0 }, },
   [(uint8_t)'_'] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 1, .e = 0, .f = 0, .g = 0 }, },
   [(uint8_t)'-'] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 0, .e = 0, .f = 0, .g = 1 }, },
   [(uint8_t)'|'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 0, .f = 0, .g = 0 }, },
   [(uint8_t)'='] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 1, .e = 0, .f = 0, .g = 1 }, },
   [(uint8_t)'>'] = { .segments = { .a = 0, .b = 0, .c = 1, .d = 1, .e = 0, .f = 0, .g = 1 }, },
   [(uint8_t)'<'] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 1, .e = 1, .f = 0, .g = 1 }, },
   [(uint8_t)'a'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 0, .g = 1 }, },
   [(uint8_t)'b'] = { .segments = { .a = 0, .b = 0, .c = 1, .d = 1, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'c'] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 1, .e = 1, .f = 0, .g = 1 }, },
   [(uint8_t)'d'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 1, .e = 1, .f = 0, .g = 1 }, },
   [(uint8_t)'e'] = { .segments = { .a = 1, .b = 1, .c = 0, .d = 1, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'f'] = { .segments = { .a = 1, .b = 0, .c = 0, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'g'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 }, },
   [(uint8_t)'h'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'i'] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 0, .e = 1, .f = 0, .g = 0 }, },
   [(uint8_t)'j'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 1, .e = 0, .f = 0, .g = 0 }, },
   [(uint8_t)'k'] = { .segments = { .a = 1, .b = 0, .c = 1, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'l'] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 0, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)'m'] = { .segments = { .a = 0, .b = 0, .c = 1, .d = 0, .e = 1, .f = 0, .g = 0 }, },
   [(uint8_t)'n'] = { .segments = { .a = 0, .b = 0, .c = 1, .d = 0, .e = 1, .f = 0, .g = 1 }, },
   [(uint8_t)'o'] = { .segments = { .a = 0, .b = 0, .c = 1, .d = 1, .e = 1, .f = 0, .g = 1 }, },
   [(uint8_t)'p'] = { .segments = { .a = 1, .b = 1, .c = 0, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'q'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 }, },
   [(uint8_t)'r'] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 0, .e = 1, .f = 0, .g = 1 }, },
   [(uint8_t)'s'] = { .segments = { .a = 1, .b = 0, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 }, },
   [(uint8_t)'t'] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 1, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'u'] = { .segments = { .a = 0, .b = 0, .c = 1, .d = 1, .e = 1, .f = 0, .g = 0 }, },
   [(uint8_t)'v'] = { .segments = { .a = 0, .b = 0, .c = 1, .d = 1, .e = 1, .f = 0, .g = 0 }, },
   [(uint8_t)'w'] = { .segments = { .a = 0, .b = 0, .c = 1, .d = 0, .e = 1, .f = 0, .g = 0 }, },
   [(uint8_t)'x'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'y'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 }, },
   [(uint8_t)'z'] = { .segments = { .a = 1, .b = 1, .c = 0, .d = 1, .e = 1, .f = 0, .g = 1 }, },
   [(uint8_t)'A'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'B'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'C'] = { .segments = { .a = 1, .b = 0, .c = 0, .d = 1, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)'D'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)'E'] = { .segments = { .a = 1, .b = 0, .c = 0, .d = 1, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'F'] = { .segments = { .a = 1, .b = 0, .c = 0, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'G'] = { .segments = { .a = 1, .b = 0, .c = 1, .d = 1, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'H'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'I'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 0, .f = 0, .g = 0 }, },
   [(uint8_t)'J'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 1, .e = 0, .f = 0, .g = 0 }, },
   [(uint8_t)'K'] = { .segments = { .a = 1, .b = 0, .c = 1, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'L'] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 1, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)'M'] = { .segments = { .a = 1, .b = 0, .c = 1, .d = 0, .e = 1, .f = 0, .g = 0 }, },
   [(uint8_t)'N'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 0, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)'O'] = { .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)'P'] = { .segments = { .a = 1, .b = 1, .c = 0, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'Q'] = { .segments = { .a = 1, .b = 1, .c = 0, .d = 1, .e = 0, .f = 1, .g = 1 }, },
   [(uint8_t)'R'] = { .segments = { .a = 1, .b = 1, .c = 0, .d = 0, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)'S'] = { .segments = { .a = 1, .b = 0, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 }, },
   [(uint8_t)'T'] = { .segments = { .a = 0, .b = 0, .c = 0, .d = 1, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'U'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)'V'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 0 }, },
   [(uint8_t)'W'] = { .segments = { .a = 0, .b = 1, .c = 0, .d = 1, .e = 0, .f = 1, .g = 0 }, },
   [(uint8_t)'X'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 0, .e = 1, .f = 1, .g = 1 }, },
   [(uint8_t)'Y'] = { .segments = { .a = 0, .b = 1, .c = 1, .d = 1, .e = 0, .f = 1, .g = 1 }, },
   [(uint8_t)'Z'] = { .segments = { .a = 1, .b = 1, .c = 0, .d = 1, .e = 1, .f = 0, .g = 1 }, }
};

#elif !defined(ASCII_7SEG_DONT_USE_LOOKUP_TABLE)

/**
 * NumLUT is a lookup table (LUT) containing the 7-segment display encodings
 * for the digit ASCII characters. It is part of the lookup table strategy for
 * the variations of this library that don't need the full range of supported
 * characters.
 */
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

#endif

/* Private Function Prototypes */

/* Public API Implementations */

/******************************************************************************/
bool Ascii7Seg_ConvertChar( char ascii_char, union Ascii7Seg_Encoding_U * buf )
{
   if ( (NULL == buf) || (ascii_char <= 0) ||
        !Ascii7Seg_IsSupportedChar(ascii_char) )
   {
      return false;
   }

#ifdef ASCII_7SEG_NUMS_ONLY

   assert( (ascii_char >= '0') && (ascii_char <= '9') );

#ifdef ASCII_7SEG_DONT_USE_LOOKUP_TABLE

   buf->segments.a = !( (ascii_char == '1') || (ascii_char == '4') );
   buf->segments.b = !( (ascii_char == '5') || (ascii_char == '6') );
   buf->segments.c = !(  ascii_char == '2');
   buf->segments.d = !( (ascii_char == '1') || (ascii_char == '4') || (ascii_char == '7') );
   buf->segments.e =  ( (ascii_char == '0') || (ascii_char == '2') || (ascii_char == '6') || (ascii_char == '8') );
   buf->segments.f = !( (ascii_char == '1') || (ascii_char == '2') || (ascii_char == '3') || (ascii_char == '7') );
   buf->segments.g = !( (ascii_char == '0') || (ascii_char == '1') || (ascii_char == '7') );

#else // Use a lookup table

   *buf = NumLUT[ ascii_char - '0' ];

#endif // ASCII_7SEG_DONT_USE_LOOKUP_TABLE

#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY) // if !ASCII_7SEG_NUMS_ONLY

   assert( ( (ascii_char >= '0') && (ascii_char <= '9') ) || 
           (ascii_char == 'E') || (ascii_char == 'e') ||
           (ascii_char == 'R') || (ascii_char == 'r') ||
           (ascii_char == 'O') || (ascii_char == 'o') );

#ifdef ASCII_7SEG_DONT_USE_LOOKUP_TABLE

   buf->segments.a = !( (ascii_char == '1') || (ascii_char == '4') || (ascii_char == 'r') || (ascii_char == 'o') );
   buf->segments.b = !( (ascii_char == '5') || (ascii_char == '6') || (ascii_char == 'E') || (ascii_char == 'r') || (ascii_char == 'o') );
   buf->segments.c = !( (ascii_char == '2') || ( (ascii_char > '9') && (ascii_char != 'o') && (ascii_char != 'O') ) ); // Letters are all greater than '9'
   buf->segments.d = !( (ascii_char == '1') || (ascii_char == '4') || (ascii_char == '7') || (ascii_char == 'R') || (ascii_char == 'r') );
   buf->segments.e =  ( (ascii_char == '0') || (ascii_char == '2') || (ascii_char == '6') || (ascii_char == '8') || (ascii_char > '9') );
   buf->segments.f = !( (ascii_char == '1') || (ascii_char == '2') || (ascii_char == '3') || (ascii_char == '7') || (ascii_char == 'r') || (ascii_char == 'o') );
   buf->segments.g = !( (ascii_char == '0') || (ascii_char == '1') || (ascii_char == '7') || (ascii_char == 'R') || (ascii_char == 'O') );

#else // Use a lookup table

   /** 
    * Additional lookup table for this nums + "error" variant of the library
    * because this plus the additional if statement make for a simple solution
    * that doesn't involve a complex hash for a LUT that combines both the digit
    * characters and the "error" (upper/lowercase) characters.
    */
   static const union Ascii7Seg_Encoding_U ErrorLUT[] =
   {                                                                                      
      {  /* e */ .segments = { .a = 1, .b = 1, .c = 0, .d = 1, .e = 1, .f = 1, .g = 1 } },
      {  /* E */ .segments = { .a = 1, .b = 0, .c = 0, .d = 1, .e = 1, .f = 1, .g = 1 } },
      {  /* r */ .segments = { .a = 0, .b = 0, .c = 0, .d = 0, .e = 1, .f = 0, .g = 1 } },
      {  /* R */ .segments = { .a = 1, .b = 1, .c = 0, .d = 0, .e = 1, .f = 1, .g = 0 } },
      {  /* o */ .segments = { .a = 0, .b = 0, .c = 1, .d = 1, .e = 1, .f = 0, .g = 1 } },
      {  /* O */ .segments = { .a = 1, .b = 1, .c = 1, .d = 1, .e = 1, .f = 1, .g = 0 } }
   };

   if ( ascii_char > '9' )
   {

#if defined(__GNUC__)
/* -Wconversion suppression:
* Specifically, the warning is:
*
*    src/ascii7seg.c:204:22: warning: conversion from 'int' to 'uint8_t' {aka 'unsigned char'} may change value [-Wconversion]
*    204 |       uint8_t hash = ((((uint8_t)ascii_char & 0x3) - 1) << 1) + (((uint8_t)ascii_char & 0x20) == 0);
*
* I'm not concerned about this here because ascii_char is constrained to one
* of a few char values, all of which work fine going through the computation.
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
      // See "Notes for Hashing.md" file at root of repo
      uint8_t hash = ((((uint8_t)ascii_char & 0x3) - 1) << 1) + (((uint8_t)ascii_char & 0x20) == 0);
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

      *buf = ErrorLUT[hash];
   }
   else
   {
      *buf = NumLUT[ ascii_char - '0' ];
   }

#endif // ASCII_7SEG_DONT_USE_LOOKUP_TABLE


#else // Full range of supported characters

#ifdef ASCII_7SEG_DONT_USE_LOOKUP_TABLE

   // FIXME: Add a non-lookup table approach to the full character range support.
   //        There isn't an obvious answer to this one for me, other than a really
   //        long and ugly logical expression chain like that of the other
   //        sections, but much worse. One can take a look at the scatter plots
   //        at the root of the repository that visualize the encoding mapping
   //        and clearly, this is not a simple closed-form function.
   //        So, for now, I'll go for this lookup table approach...
   *buf = MasterLUT[(uint8_t)ascii_char];

#else

   *buf = MasterLUT[(uint8_t)ascii_char];

#endif // ASCII_7SEG_DONT_USE_LOOKUP_TABLE

#endif // endif for macros that limit range of representable values

   // If we've reached here, we've successfully encoded the character.
   return true;
}

/******************************************************************************/
size_t Ascii7Seg_ConvertWord( const char * str,
                              size_t str_len,
                              union Ascii7Seg_Encoding_U * buf )
{
   if ( (NULL == str) || (NULL == buf) )
   {
      return false;
   }

   bool word_converted = false;
   size_t chars_converted = 0;
   while ( (str[chars_converted] != '\0') && (chars_converted < str_len) )
   {
      word_converted = Ascii7Seg_ConvertChar( str[chars_converted],
                                              &buf[chars_converted] );
      if ( !word_converted )
      {
         // Character failed to convert
         break;
      }

      chars_converted++;
   }

   return chars_converted;
}

/******************************************************************************/
bool Ascii7Seg_IsSupportedChar( char ascii_char )
{

#ifdef ASCII_7SEG_NUMS_ONLY
   if ( (ascii_char < '0') || (ascii_char > '9') )
#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)
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
#else
   if ( !isalnum(ascii_char) &&
        (ascii_char != '[') && (ascii_char != ']') &&
        (ascii_char != '(') && (ascii_char != ')') &&
        (ascii_char != '_') && (ascii_char != '-') && 
        (ascii_char != '|') && (ascii_char != '=') &&
        (ascii_char != '>') && (ascii_char != '<') )
#endif // ASCII_7SEG_NUMS_ONLY

   {
      return false;
   }

   return true;
}
