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
#include "ascii7seg_config.h"

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

// Full ASCII Encoding Lookup Table
extern const union Ascii7Seg_Encoding_U AsciiEncodingReferenceLookup[ UINT8_MAX ];

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
   union Ascii7Seg_Encoding_U enc;

   for (size_t i = 0; i < sizeof(SupportedAsciiCharacters); ++i)
   {

#ifdef ASCII_7SEG_NUMS_ONLY

      for ( char c = '0'; c <= '9'; c++ )
      {
         bool result = Ascii7Seg_ConvertChar(c, &enc);
         TEST_ASSERT_TRUE_MESSAGE(result, "Ascii7Seg_ConvertChar should succeed for supported char");
         TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)c], &enc, sizeof(enc), "Encoding mismatch");
      }

#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)

#else

#endif

   }
}

void test_Ascii7Seg_ConvertChar_InvalidChars(void)
{
   union Ascii7Seg_Encoding_U enc;

#ifdef ASCII_7SEG_NUMS_ONLY

      for ( unsigned int c = 0; c <= UINT8_MAX; c++ )
      {
         if ( ((char)c >= '0') && ((char)c <= '9') )  continue;
         bool result = Ascii7Seg_ConvertChar((char)c, &enc);
         char msg[60];
         snprintf( msg, 60, "Ascii7Seg_ConvertChar should fail for unsupported char: %c", (char)c );
         TEST_ASSERT_FALSE_MESSAGE(result, msg);
      }

#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)

#else

#endif
}

void test_Ascii7Seg_ConvertChar_NullBuf(void)
{

   bool result = Ascii7Seg_ConvertChar('1', NULL);
   TEST_ASSERT_FALSE_MESSAGE(result, "Ascii7Seg_ConvertChar should fail if buf is NULL");
}

/******************************* Convert Word *********************************/

void test_Ascii7Seg_ConvertWord_ValidString(void)
{

#ifdef ASCII_7SEG_NUMS_ONLY

   const char *str = "123";
   union Ascii7Seg_Encoding_U buf[3];
   bool result = Ascii7Seg_ConvertWord(str, 3, buf);
   char err_msg[60];
   (void)snprintf( err_msg, sizeof(err_msg), "Ascii7Seg_ConvertWord should succeed for valid string: %3s", str );
   TEST_ASSERT_TRUE_MESSAGE(result, err_msg);
   for (size_t i = 0; i < 3; ++i)
   {
      TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)str[i]], &buf[i], sizeof(union Ascii7Seg_Encoding_U));
   }

#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)

#else

#endif

}

void test_Ascii7Seg_ConvertWord_InvalidChars(void)
{

#ifdef ASCII_7SEG_NUMS_ONLY

   const char *str = "12A";
   union Ascii7Seg_Encoding_U buf[3];
   bool result = Ascii7Seg_ConvertWord(str, 3, buf);
   char err_msg[60];
   (void)snprintf( err_msg, sizeof(err_msg), "Ascii7Seg_ConvertWord should fail for string /w invalid char(s): %3s", str );
   TEST_ASSERT_FALSE_MESSAGE(result, err_msg);

#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)

#else

#endif

}

void test_Ascii7Seg_ConvertWord_NullBuf(void)
{
   const char *str = "123";
   bool result = Ascii7Seg_ConvertWord(str, 3, NULL);
   TEST_ASSERT_FALSE_MESSAGE(result, "Ascii7Seg_ConvertWord should fail if buf is NULL");
}

void test_Ascii7Seg_ConvertWord_NullStr(void)
{
   union Ascii7Seg_Encoding_U buf[3];
   bool result = Ascii7Seg_ConvertWord(NULL, 3, buf);
   TEST_ASSERT_FALSE_MESSAGE(result, "Ascii7Seg_ConvertWord should fail if str is NULL");
}

void test_Ascii7Seg_ConvertWord_ZeroLen(void)
{
   union Ascii7Seg_Encoding_U buf[1];
   bool result = Ascii7Seg_ConvertWord("A", 0, buf);
   TEST_ASSERT_FALSE_MESSAGE(result, "Ascii7Seg_ConvertWord should fail if str_len is zero");
}

