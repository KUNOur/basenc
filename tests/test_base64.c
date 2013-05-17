/* Test Base64 Functions */

#include <stdlib.h>
#include <check.h>

#include "../src/base64.h"

START_TEST (test_base64_encode_block)
{
  char str[] = "foo";
  char correct_encoded[] = "Zm9v";
  char encoded[5];

  base64_encode_block(str, encoded);

  ck_assert_str_eq(encoded, correct_encoded);
}
END_TEST

START_TEST (test_base64_encode)
{
  char str1[] = "fooba";
  char correct_encoded1[] = "Zm9vYmE=";
  char encoded[9];

  base64_encode(str1, 5, encoded);
  encoded[8] = '\0';
  ck_assert_str_eq(encoded, correct_encoded1);

  char str2[] = "f";
  char correct_encoded2[] = "Zg==";
  base64_encode(str2, 1, encoded);
  encoded[4] = '\0';
  ck_assert_str_eq(encoded, correct_encoded2);
}
END_TEST

START_TEST (test_base64_decode)
{
  char encoded[] = "Zm9vYg==";
  char correct_decoded[] = "foob";
  char decoded[7];

  base64_decode(encoded, decoded);
  decoded[5] = '\0';
  ck_assert_str_eq(decoded, correct_decoded);
}
END_TEST

Suite*
base64_suite(void)
{
  Suite *s = suite_create("Base64");

  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_base64_encode_block);
  tcase_add_test(tc_core, test_base64_encode);
  suite_add_tcase(s, tc_core);

  return s;
}

int
main(void)
{
  int number_failed;
  Suite* s = base64_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
