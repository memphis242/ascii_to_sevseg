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
#include <ctype.h>
#include <limits.h>
#include "unity.h"
#include "ascii7seg.h"
#include "ascii7seg_config.h"

/* Local Macro Definitions */

/* Datatypes */

/* Local Variables */

#if defined(ASCII_7SEG_NUMS_ONLY) || defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)
#ifdef __GNUC__
/* -Wunused-const-variable suppression:
* Specifically, the warning is:
*
* test/test_ascii7seg.c:26:19: warning: 'SupportedAsciiCharacters' defined but not used [-Wunused-const-variable=]
*    26 | static const char SupportedAsciiCharacters[] =
*       |                   ^~~~~~~~~~~~~~~~~~~~~~~~
*
* I want this warning for the largest range support build but not for the other variants.
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#endif // __GNUC__
#endif // Char range macros
static const char SupportedAsciiCharacters[] =
{
   // 0-9
   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
   // Some symbols
   '[', ']', '(', ')', '_', '-', '|', '=', '>', '<',
   // Every lowercase letter
   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
   // Every uppercase letter
   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};
#if defined(ASCII_7SEG_NUMS_ONLY) || defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif // __GNUC__
#endif // Char range macros

// Full ASCII Encoding Lookup Table
extern const union Ascii7Seg_Encoding_U AsciiEncodingReferenceLookup[ UINT8_MAX ];

/* Forward Function Declarations */

void setUp(void);
void tearDown(void);

void test_Ascii7Seg_ConvertChar_ValidChars(void);
void test_Ascii7Seg_ConvertChar_NonPackedUnionCheck(void);
void test_Ascii7Seg_ConvertChar_InvalidChars(void);
void test_Ascii7Seg_ConvertChar_NullBuf(void);

void test_Ascii7Seg_ConvertWord_ValidString(void);
void test_Ascii7Seg_ConvertWord_InvalidChars(void);
void test_Ascii7Seg_ConvertWord_NullBuf(void);
void test_Ascii7Seg_ConvertWord_NullStr(void);
void test_Ascii7Seg_ConvertWord_ZeroLen(void);

void test_Ascii7Seg_ConvertNum_PositiveNumbers(void);
void test_Ascii7Seg_ConvertNum_NegativeNumbers(void);
void test_Ascii7Seg_ConvertNum_BufferTooSmall(void);
void test_Ascii7Seg_ConvertNum_BufLenMoreThanNeeded(void);
void test_Ascii7Seg_ConvertNum_NullBuffer(void);
void test_Ascii7Seg_ConvertNum_ZeroLengthBuffer(void);
void test_Ascii7Seg_ConvertNum_LargeNumbers(void);

void test_Ascii7Seg_IsSupportedChar_AllAscii(void);


bool helper_IsSupportedChar(char c);

/* Meat of the Program */

int main(void)
{
   UNITY_BEGIN();

   RUN_TEST(test_Ascii7Seg_ConvertChar_ValidChars);
   RUN_TEST(test_Ascii7Seg_ConvertChar_NonPackedUnionCheck);
   RUN_TEST(test_Ascii7Seg_ConvertChar_InvalidChars);
   RUN_TEST(test_Ascii7Seg_ConvertChar_NullBuf);

   RUN_TEST(test_Ascii7Seg_ConvertWord_ValidString);
   RUN_TEST(test_Ascii7Seg_ConvertWord_InvalidChars);
   RUN_TEST(test_Ascii7Seg_ConvertWord_NullBuf);
   RUN_TEST(test_Ascii7Seg_ConvertWord_NullStr);
   RUN_TEST(test_Ascii7Seg_ConvertWord_ZeroLen);

   RUN_TEST(test_Ascii7Seg_ConvertNum_PositiveNumbers);
   RUN_TEST(test_Ascii7Seg_ConvertNum_NegativeNumbers);
   RUN_TEST(test_Ascii7Seg_ConvertNum_BufferTooSmall);
   RUN_TEST(test_Ascii7Seg_ConvertNum_BufLenMoreThanNeeded);
   RUN_TEST(test_Ascii7Seg_ConvertNum_NullBuffer);
   RUN_TEST(test_Ascii7Seg_ConvertNum_ZeroLengthBuffer);
   RUN_TEST(test_Ascii7Seg_ConvertNum_LargeNumbers);

   RUN_TEST(test_Ascii7Seg_IsSupportedChar_AllAscii);

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

/********************************** Helpers ***********************************/

bool helper_IsSupportedChar(char c)
{
#ifdef ASCII_7SEG_NUMS_ONLY
   if ( ( ((char)c >= '0') && ((char)c <= '9') ) || ('-' == (char)c) )
   {
      return true;
   }
#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)
   if ( ( ((char)c >= '0') && ((char)c <= '9') ) || ('-' == (char)c) ||
         (tolower((int)c) == 'e') || (tolower((int)c) == 'r') || (tolower((int)c) == 'o') )
   {
      return true;
   }
#else
   for ( size_t i = 0; i < sizeof(SupportedAsciiCharacters); i++ )
   {
      if ( SupportedAsciiCharacters[i] == c )
      {
         return true;
      }
   }
#endif

   return false;
}

/**************************** Convert Single Char *****************************/

void test_Ascii7Seg_ConvertChar_ValidChars(void)
{
   union Ascii7Seg_Encoding_U enc;
   bool result;
   char err_msg[2];
   err_msg[0] = '\0';
   err_msg[1] = '\0';

#ifdef ASCII_7SEG_NUMS_ONLY

   for ( char c = '0'; c <= '9'; c++ )
   {
      result = Ascii7Seg_ConvertChar(c, &enc);
      err_msg[0] = c;
      TEST_ASSERT_TRUE_MESSAGE(result, err_msg);
#ifdef ASCII_7SEG_BIT_PACK
      TEST_ASSERT_EQUAL_UINT8_MESSAGE(AsciiEncodingReferenceLookup[(uint8_t)c].encoding_as_val, enc.encoding_as_val, err_msg);
#else
      TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)c], &enc, sizeof(enc), err_msg);
#endif
   }

   result = Ascii7Seg_ConvertChar('-', &enc);
   err_msg[0] = '-';
   TEST_ASSERT_TRUE_MESSAGE(result, err_msg);
#ifdef ASCII_7SEG_BIT_PACK
   TEST_ASSERT_EQUAL_UINT8_MESSAGE(AsciiEncodingReferenceLookup[(uint8_t)'-'].encoding_as_val, enc.encoding_as_val, err_msg);
#else
   TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)'-'], &enc, sizeof(enc), err_msg);
#endif

#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)

   for ( char c = '0'; c <= '9'; c++ )
   {
      result = Ascii7Seg_ConvertChar(c, &enc);
      err_msg[0] = c;
      TEST_ASSERT_TRUE_MESSAGE(result, err_msg);
#ifdef ASCII_7SEG_BIT_PACK
      TEST_ASSERT_EQUAL_UINT8_MESSAGE(AsciiEncodingReferenceLookup[(uint8_t)c].encoding_as_val, enc.encoding_as_val, err_msg);
#else
      TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)c], &enc, sizeof(enc), err_msg);
#endif
   }

   result = Ascii7Seg_ConvertChar('-', &enc);
   err_msg[0] = '-';
   TEST_ASSERT_TRUE_MESSAGE(result, err_msg);
#ifdef ASCII_7SEG_BIT_PACK
   TEST_ASSERT_EQUAL_UINT8_MESSAGE(AsciiEncodingReferenceLookup[(uint8_t)'-'].encoding_as_val, enc.encoding_as_val, err_msg);
#else
   TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)'-'], &enc, sizeof(enc), err_msg);
#endif

   result = Ascii7Seg_ConvertChar('E', &enc);
   TEST_ASSERT_TRUE_MESSAGE(result, "E");
#ifdef ASCII_7SEG_BIT_PACK
   TEST_ASSERT_EQUAL_UINT8_MESSAGE(AsciiEncodingReferenceLookup[(uint8_t)'E'].encoding_as_val, enc.encoding_as_val, "E");
#else
   TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)'E'], &enc, sizeof(enc), "E");
#endif

   result = Ascii7Seg_ConvertChar('e', &enc);
   TEST_ASSERT_TRUE_MESSAGE(result, "e");
#ifdef ASCII_7SEG_BIT_PACK
   TEST_ASSERT_EQUAL_UINT8_MESSAGE(AsciiEncodingReferenceLookup[(uint8_t)'e'].encoding_as_val, enc.encoding_as_val, "e");
#else
   TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)'e'], &enc, sizeof(enc), "e");
#endif

   result = Ascii7Seg_ConvertChar('R', &enc);
   TEST_ASSERT_TRUE_MESSAGE(result, "R");
#ifdef ASCII_7SEG_BIT_PACK
   TEST_ASSERT_EQUAL_UINT8_MESSAGE(AsciiEncodingReferenceLookup[(uint8_t)'R'].encoding_as_val, enc.encoding_as_val, "R");
#else
   TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)'R'], &enc, sizeof(enc), "R");
#endif

   result = Ascii7Seg_ConvertChar('r', &enc);
   TEST_ASSERT_TRUE_MESSAGE(result, "r");
#ifdef ASCII_7SEG_BIT_PACK
   TEST_ASSERT_EQUAL_UINT8_MESSAGE(AsciiEncodingReferenceLookup[(uint8_t)'r'].encoding_as_val, enc.encoding_as_val, "r");
#else
   TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)'r'], &enc, sizeof(enc), "r");
#endif

   result = Ascii7Seg_ConvertChar('O', &enc);
   TEST_ASSERT_TRUE_MESSAGE(result, "O");
#ifdef ASCII_7SEG_BIT_PACK
   TEST_ASSERT_EQUAL_UINT8_MESSAGE(AsciiEncodingReferenceLookup[(uint8_t)'O'].encoding_as_val, enc.encoding_as_val, "O");
#else
   TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)'O'], &enc, sizeof(enc), "O");
#endif

   result = Ascii7Seg_ConvertChar('o', &enc);
   TEST_ASSERT_TRUE_MESSAGE(result, "o");
#ifdef ASCII_7SEG_BIT_PACK
   TEST_ASSERT_EQUAL_UINT8_MESSAGE(AsciiEncodingReferenceLookup[(uint8_t)'o'].encoding_as_val, enc.encoding_as_val, "o");
#else
   TEST_ASSERT_EQUAL_MEMORY_MESSAGE(&AsciiEncodingReferenceLookup[(uint8_t)'o'], &enc, sizeof(enc), "o");
#endif

#else

   for ( size_t i = 0; i < sizeof(SupportedAsciiCharacters); i++ )
   {
      result = Ascii7Seg_ConvertChar(SupportedAsciiCharacters[i], &enc);
      err_msg[0] = SupportedAsciiCharacters[i];
      TEST_ASSERT_TRUE_MESSAGE(result, err_msg);
#ifdef ASCII_7SEG_BIT_PACK
      TEST_ASSERT_EQUAL_UINT8_MESSAGE(
         AsciiEncodingReferenceLookup[(size_t)SupportedAsciiCharacters[i]].encoding_as_val,
         enc.encoding_as_val,
         err_msg);
#else
      TEST_ASSERT_EQUAL_MEMORY_MESSAGE(
         &AsciiEncodingReferenceLookup[(size_t)SupportedAsciiCharacters[i]],
         &enc,
         sizeof(enc),
         err_msg);
#endif
   }

#endif

}

void test_Ascii7Seg_ConvertChar_NonPackedUnionCheck(void)
{
   union Ascii7Seg_Encoding_U enc;
   bool result;

   result = Ascii7Seg_ConvertChar('0', &enc);   // All variants support '0'
   TEST_ASSERT_TRUE_MESSAGE(result, "0");
   // '0' would render as all segments on except the middle on (g)
#ifdef ASCII_7SEG_BIT_PACK
   TEST_ASSERT_EQUAL_UINT8_MESSAGE(
      0x3F,
      enc.encoding_as_val & ASCII_7SEG_BIT_PACK_MASK,
      "0" );
#else
   TEST_ASSERT_TRUE( enc.encoding_as_val[0] );
   TEST_ASSERT_TRUE( enc.segments.a );
   TEST_ASSERT_TRUE( enc.encoding_as_val[1] );
   TEST_ASSERT_TRUE( enc.segments.b );
   TEST_ASSERT_TRUE( enc.encoding_as_val[2] );
   TEST_ASSERT_TRUE( enc.segments.c );
   TEST_ASSERT_TRUE( enc.encoding_as_val[3] );
   TEST_ASSERT_TRUE( enc.segments.d );
   TEST_ASSERT_TRUE( enc.encoding_as_val[4] );
   TEST_ASSERT_TRUE( enc.segments.e );
   TEST_ASSERT_TRUE( enc.encoding_as_val[5] );
   TEST_ASSERT_TRUE( enc.segments.f );
   TEST_ASSERT_FALSE( enc.encoding_as_val[6] );
   TEST_ASSERT_FALSE( enc.segments.g );
#endif

}

void test_Ascii7Seg_ConvertChar_InvalidChars(void)
{
   union Ascii7Seg_Encoding_U enc;

   for ( int c = CHAR_MIN; c <= CHAR_MAX; c++ )
   {
      if ( helper_IsSupportedChar((char)c) )
      {
         continue;
      }
      bool result = Ascii7Seg_ConvertChar((char)c, &enc);
      char msg[60];
      snprintf( msg, 60, "Ascii7Seg_ConvertChar should fail for unsupported char: %c", (char)c );
      TEST_ASSERT_FALSE_MESSAGE(result, msg);

   }
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
   const char str[] = "-123";
#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)
   const char str[] = "err123";
#else
   const char str[] = "abc123|_-";
#endif

   union Ascii7Seg_Encoding_U buf[ sizeof(str) ];
   size_t converted = Ascii7Seg_ConvertWord(str, sizeof(str), buf);
   char err_msg[70];
   (void)snprintf( err_msg, sizeof(err_msg), "Ascii7Seg_ConvertWord should convert all chars for valid string: %9s", str );
   TEST_ASSERT_EQUAL_MESSAGE(sizeof(str) - 1, converted, err_msg);
   for (size_t i = 0; i < sizeof(str) - 1; ++i)
   {
      (void)snprintf( err_msg, sizeof(err_msg), "%s : %c", str, str[i] );
#ifdef ASCII_7SEG_BIT_PACK
      TEST_ASSERT_EQUAL_UINT8_MESSAGE(
         AsciiEncodingReferenceLookup[(uint8_t)str[i]].encoding_as_val & ASCII_7SEG_BIT_PACK_MASK,
         buf[i].encoding_as_val & ASCII_7SEG_BIT_PACK_MASK,
         err_msg );
#else
      TEST_ASSERT_EQUAL_MEMORY_MESSAGE(
         &AsciiEncodingReferenceLookup[(uint8_t)str[i]],
         &buf[i],
         sizeof(union Ascii7Seg_Encoding_U),
         err_msg );
#endif
   }
}

void test_Ascii7Seg_ConvertWord_InvalidChars(void)
{

#ifdef ASCII_7SEG_NUMS_ONLY
   const char * str1 = "A23";
   const char * str2 = "1B3";
   const char * str3 = "12_";
   const char * str4 = "___";
#elif defined(ASCII_7SEG_NUMS_AND_ERROR_ONLY)
   const char * str1 = "!4e";
   const char * str2 = "1*3";
   const char * str3 = "12>";
   const char * str4 = "___";
#else
   const char * str1 = ",2Z";
   const char * str2 = "Z,1";
   const char * str3 = "5K,";
   const char * str4 = "...";
#endif

   union Ascii7Seg_Encoding_U buf[3];
   size_t converted;
   char err_msg[60];

   converted = Ascii7Seg_ConvertWord(str1, 3, buf);
   (void)snprintf( err_msg, sizeof(err_msg), "Ascii7Seg_ConvertWord should stop at first invalid char in: %3s", str1 );
   TEST_ASSERT_LESS_THAN_MESSAGE(3, converted, err_msg);

   converted = Ascii7Seg_ConvertWord(str2, 3, buf);
   (void)snprintf( err_msg, sizeof(err_msg), "Ascii7Seg_ConvertWord should stop at first invalid char in: %3s", str2 );
   TEST_ASSERT_LESS_THAN_MESSAGE(3, converted, err_msg);

   converted = Ascii7Seg_ConvertWord(str3, 3, buf);
   (void)snprintf( err_msg, sizeof(err_msg), "Ascii7Seg_ConvertWord should stop at first invalid char in: %3s", str3 );
   TEST_ASSERT_LESS_THAN_MESSAGE(3, converted, err_msg);

   converted = Ascii7Seg_ConvertWord(str4, 3, buf);
   (void)snprintf( err_msg, sizeof(err_msg), "Ascii7Seg_ConvertWord should stop at first invalid char in: %3s", str4 );
   TEST_ASSERT_LESS_THAN_MESSAGE(3, converted, err_msg);
}

void test_Ascii7Seg_ConvertWord_NullBuf(void)
{
   const char *str = "123";
   size_t converted = Ascii7Seg_ConvertWord(str, 3, NULL);
   TEST_ASSERT_EQUAL_MESSAGE(0, converted, "Ascii7Seg_ConvertWord should return 0 if buf is NULL");
}

void test_Ascii7Seg_ConvertWord_NullStr(void)
{
   union Ascii7Seg_Encoding_U buf[3];
   size_t converted = Ascii7Seg_ConvertWord(NULL, 3, buf);
   TEST_ASSERT_EQUAL_MESSAGE(0, converted, "Ascii7Seg_ConvertWord should return 0 if str is NULL");
}

void test_Ascii7Seg_ConvertWord_ZeroLen(void)
{
   union Ascii7Seg_Encoding_U buf[1];
   size_t converted = Ascii7Seg_ConvertWord("A", 0, buf);
   TEST_ASSERT_EQUAL_MESSAGE(0, converted, "Ascii7Seg_ConvertWord should return 0 if str_len is zero");
}

/****************************** Convert Number ********************************/
void test_Ascii7Seg_ConvertNum_PositiveNumbers(void)
{
   union Ascii7Seg_Encoding_U buf[32];
   // Test single digit
   bool result = Ascii7Seg_ConvertNum(5, buf, 1);
   TEST_ASSERT_TRUE(result);
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'5'], &buf[0], sizeof(buf[0]));

   // Test multi-digit
   result = Ascii7Seg_ConvertNum(123, buf, 3);
   TEST_ASSERT_TRUE(result);
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'1'], &buf[0], sizeof(buf[0]));
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'2'], &buf[1], sizeof(buf[1]));
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'3'], &buf[2], sizeof(buf[2]));

   // Test zero
   result = Ascii7Seg_ConvertNum(0, buf, 1);
   TEST_ASSERT_TRUE(result);
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'0'], &buf[0], sizeof(buf[0]));
}

void test_Ascii7Seg_ConvertNum_NegativeNumbers(void)
{
   union Ascii7Seg_Encoding_U buf[32];
   // Test negative single digit
   bool result = Ascii7Seg_ConvertNum(-7, buf, 2);
   TEST_ASSERT_TRUE(result);
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'-'], &buf[0], sizeof(buf[0]));
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'7'], &buf[1], sizeof(buf[1]));

   // Test negative multi-digit
   result = Ascii7Seg_ConvertNum(-42, buf, 3);
   TEST_ASSERT_TRUE(result);
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'-'], &buf[0], sizeof(buf[0]));
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'4'], &buf[1], sizeof(buf[1]));
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'2'], &buf[2], sizeof(buf[2]));
}

void test_Ascii7Seg_ConvertNum_BufferTooSmall(void)
{
   union Ascii7Seg_Encoding_U buf[2];
   // Needs 3 slots for "-10"
   bool result = Ascii7Seg_ConvertNum(-10, buf, 2);
   TEST_ASSERT_FALSE(result);

   // Needs 2 slots for "10"
   result = Ascii7Seg_ConvertNum(10, buf, 1);
   TEST_ASSERT_FALSE(result);
}

void test_Ascii7Seg_ConvertNum_BufLenMoreThanNeeded(void)
{
   union Ascii7Seg_Encoding_U buf[5];
   // Should still succeed
   bool result = Ascii7Seg_ConvertNum(12, buf, 5);
   TEST_ASSERT_TRUE(result);
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'1'], &buf[0], sizeof(buf[0]));
   TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)'2'], &buf[1], sizeof(buf[0]));
}


void test_Ascii7Seg_ConvertNum_NullBuffer(void)
{
   bool result = Ascii7Seg_ConvertNum(123, NULL, 3);
   TEST_ASSERT_FALSE(result);
}

void test_Ascii7Seg_ConvertNum_ZeroLengthBuffer(void)
{
   union Ascii7Seg_Encoding_U buf[1];
   bool result = Ascii7Seg_ConvertNum(3, buf, 0);
   TEST_ASSERT_FALSE(result);
}

void test_Ascii7Seg_ConvertNum_LargeNumbers(void)
{
   union Ascii7Seg_Encoding_U buf[32];
   // INT64_MAX: 9223372036854775807 (19 digits)
   bool result = Ascii7Seg_ConvertNum(INT64_MAX, buf, 19);
   TEST_ASSERT_TRUE(result);
   const char *max_str = "9223372036854775807";
   for (size_t i = 0; i < 19; ++i) {
      TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)max_str[i]], &buf[i], sizeof(buf[0]));
   }

   // INT64_MIN: -9223372036854775808 (20 chars: '-' + 19 digits)
   result = Ascii7Seg_ConvertNum(INT64_MIN, buf, 20);
   TEST_ASSERT_TRUE(result);
   const char *min_str = "-9223372036854775808";
   for (size_t i = 0; i < 20; ++i) {
      TEST_ASSERT_EQUAL_MEMORY(&AsciiEncodingReferenceLookup[(uint8_t)min_str[i]], &buf[i], sizeof(buf[0]));
   }
}

/******************************* Is Supported? ********************************/

void test_Ascii7Seg_IsSupportedChar_AllAscii(void)
{
   for (int c = 0; c <= 127; ++c)
   {
      bool expected = helper_IsSupportedChar((char)c);
      char msg[2];
      msg[0] = (char)c;
      msg[1] = '\0';
      TEST_ASSERT_EQUAL_MESSAGE(expected, Ascii7Seg_IsSupportedChar((char)c), msg);
   }
}
