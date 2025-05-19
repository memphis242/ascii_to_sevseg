/*!
 * @file    test_ascii7seg.c
 * @brief   Test file for the the ASCII to 7 Segment Encoder component.
 *
 * @author  Abdullah Almosalami @memphis242
 * @date    May 18, 2025
 * @copyright MIT License
 */

/* File Inclusions */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "ascii7seg.h"

/* Local Macro Definitions */

/* Datatypes */

/* Local Variables */

static const char SupportedAsciiCharacters[] =
{
   // 0-9
   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
   // Some symbols
   '[', ']', '_', '-', '|', '=', '>', '<',
   // Every lowercase letter
   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
   // Every uppercase letter
   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

static const struct Ascii7Seg_Encoding_S ReferenceLookup[ UINT8_MAX ] =
{
   ['0'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['1'] =
      {
               .a = 0;
         .f = 0;     .b = 1;
               .g = 0;
         .e = 0;     .c = 1;
               .d = 0;
      },
   ['2'] =
      {
               .a = 1;
         .f = 0;     .b = 1;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 1;
      },
   ['3'] =
      {
               .a = 1;
         .f = 0;     .b = 1;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['4'] =
      {
               .a = 0;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 0;
      },
   ['5'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['6'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['7'] =
      {
               .a = 1;
         .f = 0;     .b = 1;
               .g = 0;
         .e = 0;     .c = 1;
               .d = 0;
      },
   ['8'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['9'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['['] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 0;
         .e = 1;     .c = 0;
               .d = 1;
      },
   [']'] =
      {
               .a = 1;
         .f = 0;     .b = 1;
               .g = 0;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['_'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 0;
         .e = 0;     .c = 0;
               .d = 1;
      },
   ['-'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 1;
         .e = 0;     .c = 0;
               .d = 0;
      },
   ['|'] =
      {
               .a = 0;
         .f = 0;     .b = 1;
               .g = 0;
         .e = 0;     .c = 1;
               .d = 0;
      },
   ['='] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 1;
         .e = 0;     .c = 0;
               .d = 1;
      },
   ['>'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['<'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 1;
      },
   ['a'] =
      {
               .a = 1;
         .f = 0;     .b = 1;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['b'] =
      {
               .a = 0;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['c'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 1;
      },
   ['d'] =
      {
               .a = 0;
         .f = 0;     .b = 1;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['e'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 1;
      },
   ['f'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 0;
      },
   ['g'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['h'] =
      {
               .a = 0;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['i'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 0;
         .e = 1;     .c = 0;
               .d = 0;
      },
   ['j'] =
      {
               .a = 0;
         .f = 0;     .b = 1;
               .g = 0;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['k'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['l'] =
      {
               .a = 0;
         .f = 1;     .b = 0;
               .g = 0;
         .e = 1;     .c = 0;
               .d = 0;
      },
   ['m'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['n'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['p'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 0;
      },
   ['q'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['r'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 0;
      },
   ['s'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['t'] =
      {
               .a = 0;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 1;
      },
   ['u'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['v'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['w'] =
      {
               .a = 0;
         .f = 0;     .b = 0;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['x'] =
      {
               .a = 0;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['y'] =
      {
               .a = 0;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['z'] =
      {
               .a = 1;
         .f = 0;     .b = 1;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 1;
      },
   ['A'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['B'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['C'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 0;
         .e = 1;     .c = 0;
               .d = 1;
      },
   ['D'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['E'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 1;
      },
   ['F'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 0;
      },
   ['G'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['H'] =
      {
               .a = 0;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['I'] =
      {
               .a = 0;
         .f = 0;     .b = 1;
               .g = 0;
         .e = 0;     .c = 1;
               .d = 0;
      },
   ['J'] =
      {
               .a = 0;
         .f = 0;     .b = 1;
               .g = 0;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['K'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['L'] =
      {
               .a = 0;
         .f = 1;     .b = 0;
               .g = 0;
         .e = 1;     .c = 0;
               .d = 1;
      },
   ['M'] =
      {
               .a = 1;
         .f = 0;     .b = 0;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['N'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['O'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['P'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 0;
      },
   ['Q'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 0;     .c = 0;
               .d = 1;
      },
   ['R'] =
      {
               .a = 1;
         .f = 1;     .b = 1;
               .g = 0;
         .e = 1;     .c = 0;
               .d = 0;
      },
   ['S'] =
      {
               .a = 1;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['T'] =
      {
               .a = 0;
         .f = 1;     .b = 0;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 1;
      },
   ['U'] =
      {
               .a = 0;
         .f = 1;     .b = 1;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['V'] =
      {
               .a = 0;
         .f = 1;     .b = 1;
               .g = 0;
         .e = 1;     .c = 1;
               .d = 1;
      },
   ['W'] =
      {
               .a = 0;
         .f = 1;     .b = 1;
               .g = 0;
         .e = 0;     .c = 0;
               .d = 1;
      },
   ['X'] =
      {
               .a = 0;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 1;     .c = 1;
               .d = 0;
      },
   ['Y'] =
      {
               .a = 0;
         .f = 1;     .b = 1;
               .g = 1;
         .e = 0;     .c = 1;
               .d = 1;
      },
   ['Z'] =
      {
               .a = 1;
         .f = 0;     .b = 1;
               .g = 1;
         .e = 1;     .c = 0;
               .d = 1;
      },
};

/* Forward Function Declarations */

void setUp(void);
void tearDown(void);

void test_Ascii7Seg_ConvertChar_ValidChars(void);
void test_Ascii7Seg_ConvertChar_InvalidChars(void);
void test_Ascii7Seg_ConvertChar_NullBuf(void);
void test_Ascii7Seg_ConvertWord_ValidString(void);
void test_Ascii7Seg_ConvertWord_InvalidChars(void);
void test_Ascii7Seg_ConvertWord_NullBuf(void);
void test_Ascii7Seg_ConvertWord_NullStr(void);
void test_Ascii7Seg_ConvertWord_ZeroLen(void);

/* Meat of the Program */

int main(void)
{
   UNITY_BEGIN();

   RUN_TEST(test_Ascii7Seg_ConvertChar_ValidChars);
   RUN_TEST(test_Ascii7Seg_ConvertChar_InvalidChars);
   RUN_TEST(test_Ascii7Seg_ConvertChar_NullBuf);

   RUN_TEST(test_Ascii7Seg_ConvertWord_ValidString);
   RUN_TEST(test_Ascii7Seg_ConvertWord_InvalidChars);
   RUN_TEST(test_Ascii7Seg_ConvertWord_NullBuf);
   RUN_TEST(test_Ascii7Seg_ConvertWord_NullStr);
   RUN_TEST(test_Ascii7Seg_ConvertWord_ZeroLen);

   return UNITY_END();
}

/********************************* Test Setup *********************************/

void setUp(void)
{
   // Do nothing
}

void tearDown(void)
{
   // Do nothing
}

/**************************** Convert Single Char *****************************/

void test_Ascii7Seg_ConvertChar_ValidChars(void)
{
   struct Ascii7Seg_Encoding_S enc;
   for (size_t i = 0; i < sizeof(SupportedAsciiCharacters); ++i) {
      char c = SupportedAsciiCharacters[i];
      bool result = Ascii7Seg_ConvertChar(c, &enc);
      TEST_ASSERT_TRUE_MESSAGE(result, "Ascii7Seg_ConvertChar should succeed for supported char");
      TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&ReferenceLookup[(uint8_t)c], &enc, sizeof(enc), "Encoding mismatch");
   }
}

void test_Ascii7Seg_ConvertChar_InvalidChars(void)
{
   struct Ascii7Seg_Encoding_S enc;
   // Pick a char not in SupportedAsciiCharacters, e.g. '@'
   bool result = Ascii7Seg_ConvertChar('@', &enc);
   TEST_ASSERT_FALSE_MESSAGE(result, "Ascii7Seg_ConvertChar should fail for unsupported char");
}

void test_Ascii7Seg_ConvertChar_NullBuf(void)
{
   bool result = Ascii7Seg_ConvertChar('A', NULL);
   TEST_ASSERT_FALSE_MESSAGE(result, "Ascii7Seg_ConvertChar should fail if buf is NULL");
}

/******************************* Convert Word *********************************/

void test_Ascii7Seg_ConvertWord_ValidString(void)
{
   const char *str = "Ab1";
   struct Ascii7Seg_Encoding_S buf[3];
   bool result = Ascii7Seg_ConvertWord(str, 3, buf);
   TEST_ASSERT_TRUE_MESSAGE(result, "Ascii7Seg_ConvertWord should succeed for valid string");
   for (size_t i = 0; i < 3; ++i) {
      TEST_ASSERT_EQUAL_MEMORY(&ReferenceLookup[(uint8_t)str[i]], &buf[i], sizeof(struct Ascii7Seg_Encoding_S));
   }
}

void test_Ascii7Seg_ConvertWord_InvalidChars(void)
{
   const char *str = "A@b";
   struct Ascii7Seg_Encoding_S buf[3];
   bool result = Ascii7Seg_ConvertWord(str, 3, buf);
   TEST_ASSERT_FALSE_MESSAGE(result, "Ascii7Seg_ConvertWord should fail if string contains unsupported char");
}

void test_Ascii7Seg_ConvertWord_NullBuf(void)
{
   const char *str = "Ab1";
   bool result = Ascii7Seg_ConvertWord(str, 3, NULL);
   TEST_ASSERT_FALSE_MESSAGE(result, "Ascii7Seg_ConvertWord should fail if buf is NULL");
}

void test_Ascii7Seg_ConvertWord_NullStr(void)
{
   struct Ascii7Seg_Encoding_S buf[3];
   bool result = Ascii7Seg_ConvertWord(NULL, 3, buf);
   TEST_ASSERT_FALSE_MESSAGE(result, "Ascii7Seg_ConvertWord should fail if str is NULL");
}

void test_Ascii7Seg_ConvertWord_ZeroLen(void)
{
   struct Ascii7Seg_Encoding_S buf[1];
   bool result = Ascii7Seg_ConvertWord("A", 0, buf);
   TEST_ASSERT_FALSE_MESSAGE(result, "Ascii7Seg_ConvertWord should fail if str_len is zero");
}

