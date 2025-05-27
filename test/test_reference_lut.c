/*!
 * @file    test_reference_lut.c
 * @brief   Reference ASCII lookup table for all the encodings.
 *
 * @author  Abdullah Almosalami @memphis242
 * @date    May 26, 2025
 * @copyright MIT License
 */
#include <stdint.h>
#include "ascii7seg.h"

const union Ascii7Seg_Encoding_U AsciiEncodingReferenceLookup[ UINT8_MAX ] =
{
   ['0'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['1'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 1,
               .g = 0,
         .e = 0,     .c = 1,
               .d = 0
         }
      },
   ['2'] =
      {
         .segments =
         {
               .a = 1,
         .f = 0,     .b = 1,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   ['3'] =
      {
         .segments =
         {
               .a = 1,
         .f = 0,     .b = 1,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['4'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 0
         }
      },
   ['5'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['6'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['7'] =
      {
         .segments =
         {
               .a = 1,
         .f = 0,     .b = 1,
               .g = 0,
         .e = 0,     .c = 1,
               .d = 0
         }
      },
   ['8'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['9'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['['] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 0,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   [']'] =
      {
         .segments =
         {
               .a = 1,
         .f = 0,     .b = 1,
               .g = 0,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['_'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 0,
         .e = 0,     .c = 0,
               .d = 1
         }
      },
   ['-'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 1,
         .e = 0,     .c = 0,
               .d = 0
         }
      },
   ['|'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 1,
               .g = 0,
         .e = 0,     .c = 1,
               .d = 0
         }
      },
   ['='] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 1,
         .e = 0,     .c = 0,
               .d = 1
         }
      },
   ['>'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['<'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   ['a'] =
      {
         .segments =
         {
               .a = 1,
         .f = 0,     .b = 1,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['b'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['c'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   ['d'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 1,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['e'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   ['f'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 0
         }
      },
   ['g'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['h'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['i'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 0,
         .e = 1,     .c = 0,
               .d = 0
         }
      },
   ['j'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 1,
               .g = 0,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['k'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['l'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 0,
               .g = 0,
         .e = 1,     .c = 0,
               .d = 0
         }
      },
   ['m'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['n'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['p'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 0
         }
      },
   ['q'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['r'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 0
         }
      },
   ['s'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['t'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   ['u'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['v'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['w'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 0,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['x'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['y'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['z'] =
      {
         .segments =
         {
               .a = 1,
         .f = 0,     .b = 1,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   ['A'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['B'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['C'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 0,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   ['D'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['E'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   ['F'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 0
         }
      },
   ['G'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['H'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['I'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 1,
               .g = 0,
         .e = 0,     .c = 1,
               .d = 0
         }
      },
   ['J'] =
      {
         .segments =
         {
               .a = 0,
         .f = 0,     .b = 1,
               .g = 0,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['K'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['L'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 0,
               .g = 0,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   ['M'] =
      {
         .segments =
         {
               .a = 1,
         .f = 0,     .b = 0,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['N'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['O'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['P'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 0
         }
      },
   ['Q'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 0,     .c = 0,
               .d = 1
         }
      },
   ['R'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 1,
               .g = 0,
         .e = 1,     .c = 0,
               .d = 0
         }
      },
   ['S'] =
      {
         .segments =
         {
               .a = 1,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['T'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 0,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
   ['U'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 1,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['V'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 1,
               .g = 0,
         .e = 1,     .c = 1,
               .d = 1
         }
      },
   ['W'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 1,
               .g = 0,
         .e = 0,     .c = 0,
               .d = 1
         }
      },
   ['X'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 1,     .c = 1,
               .d = 0
         }
      },
   ['Y'] =
      {
         .segments =
         {
               .a = 0,
         .f = 1,     .b = 1,
               .g = 1,
         .e = 0,     .c = 1,
               .d = 1
         }
      },
   ['Z'] =
      {
         .segments =
         {
               .a = 1,
         .f = 0,     .b = 1,
               .g = 1,
         .e = 1,     .c = 0,
               .d = 1
         }
      },
};