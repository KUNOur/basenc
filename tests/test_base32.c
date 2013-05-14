#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "../src/base32.h"

START_TEST (test_base32)
{
  char str[] = "foobar";
  char correct_encoded[] = "MZXW6YTBOI======";

  char *encoded = NULL;
  int encoded_len = strlen(str) * 2 + 1;
  printf("[test_base32] encoded_len = %d\n", encoded_len);
  encoded = malloc(encoded_len);

  int ret = base32_encode(str, strlen(str), encoded);

  ck_assert_int_eq(ret, 1);
  ck_assert_str_eq (encoded, correct_encoded);

  free(encoded);
}
END_TEST

START_TEST (test_base32_encode_block)
{
  char str[] = "TEST.";
  char correct_encoded[] = "KRCVGVBO";

  char encoded[9];

  base32_encode_block(str, encoded);
  encoded[8] = '\0';

  printf("encoded = \"%s\"\n", encoded);

  ck_assert_str_eq(encoded, correct_encoded);
}
END_TEST

START_TEST (test_base32_encode_small_block)
{
  char str1[] = "f";
  char correct_encoded1[] = "MY======";
  char str2[] = "fo";
  char correct_encoded2[] = "MZXQ====";
  char str3[] = "foo";
  char correct_encoded3[] = "MZXW6===";
  char str4[] = "foob";
  char correct_encoded4[] = "MZXW6YQ=";

  char encoded[9];

  base32_encode_small_block(str1, 1, encoded);
  encoded[8] = '\0';
  ck_assert_str_eq(encoded, correct_encoded1);

  base32_encode_small_block(str2, 2, encoded);
  encoded[8] = '\0';
  ck_assert_str_eq(encoded, correct_encoded2);

  base32_encode_small_block(str3, 3, encoded);
  encoded[8] = '\0';
  ck_assert_str_eq(encoded, correct_encoded3);

  base32_encode_small_block(str4, 4, encoded);
  encoded[8] = '\0';
  ck_assert_str_eq(encoded, correct_encoded4);
}
END_TEST

START_TEST (test_base32_decode_block)
{
  char encoded[] = "fooba";
  char correct_decoded[] = "MZXW6YTB";
  base32_byte decoded[4];

  base32_decode_block(encoded, decoded);
  decoded[4] = '\0';

  ck_assert_str_eq((char*)decoded, correct_decoded);
}
END_TEST

Suite*
base32_suite(void)
{
  Suite* s = suite_create("Base32");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test (tc_core, test_base32_encode_block);
  tcase_add_test (tc_core, test_base32);
  tcase_add_test (tc_core, test_base32_encode_small_block);
  //tcase_add_test (tc_core, test_base32_decode_block);
  suite_add_tcase(s, tc_core);

  return s;
}

int
main(void)
{
  int number_failed;
  Suite *s = base32_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
